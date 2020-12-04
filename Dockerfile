FROM emscripten/emsdk:2.0.6



RUN echo "## Start building" \
    \
&&	echo "## Update and install packages" \
    &&  apt-get -qq -y update \
    # mitigate problem with create symlink to man
    &&  mkdir -p /usr/share/man/man1/ \
    &&  apt-get -qq install -y --no-install-recommends \
            libxml2 \
            wget \
            git-core \
            ca-certificates \
            build-essential \
            file \
            python python-pip \
            python3 python3-pip \
			cmake \ 
			pkg-config \
			vim \
    \
&& apt-get clean \
&&  echo "## Done"

RUN echo "## Create Testing Script" \
    &&  printf '#!/bin/sh\n'                                   >  ${EMSDK}/test.sh \
    &&  printf 'set -e\n'                                      >> ${EMSDK}/test.sh \
    &&  printf 'which asm2wasm\n'                              >> ${EMSDK}/test.sh \
    &&  printf 'which llvm-ar\n'                               >> ${EMSDK}/test.sh \
    &&  printf 'which emsdk\n'                                 >> ${EMSDK}/test.sh \
    &&  printf 'node --version\n'                              >> ${EMSDK}/test.sh \
    &&  printf 'npm --version\n'                               >> ${EMSDK}/test.sh \
    &&  printf 'python --version\n'                            >> ${EMSDK}/test.sh \
    &&  printf 'pip --version\n'                               >> ${EMSDK}/test.sh \
    &&  printf 'python3 --version\n'                           >> ${EMSDK}/test.sh \
    &&  printf 'pip3 --version\n'                              >> ${EMSDK}/test.sh \
    &&  printf 'em++ --version\n'                              >> ${EMSDK}/test.sh \
    &&  printf 'emcc --version\n'                              >> ${EMSDK}/test.sh \
    &&  printf 'find ${EMSDK} -name "*.pyc" -exec rm {} \\;\n' >> ${EMSDK}/test.sh \
    \
    &&  chmod +x ${EMSDK}/test.sh \
    \
&&  echo "## Done"


RUN echo "## Pre-populate emscripten cache" \
    # use embuilder for some common cases
    &&  embuilder.py build --lto \
        libc \
        libc_rt_wasm \
        libc++ \
        libc++-noexcept \
        libc++abi-noexcept \
        libcompiler_rt \
        libdlmalloc \
        libdlmalloc-debug \
        libpthread_stub \
        libsockets \
        # Added freetype,sdl2,sdl2-image,sdl2-ttf,sdl2-net,zlib
    &&  embuilder.py build \
        freetype \
        sdl2 \
        sdl2-image \
        libpng \
        sdl2-image-png \
        sdl2-ttf \ 
        zlib \
&& echo "## Done"

RUN echo "## Build FreeType2" \
	&& git clone https://github.com/freetype/freetype2.git \
	&& cd freetype2 && mkdir build && cd build \
	&& emcmake cmake .. \
	&& emmake make \
	&& emmake make install \
	&& cd .. && cd .. \
&& echo "## Done"
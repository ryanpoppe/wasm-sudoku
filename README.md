# wasm-sudoku
This is a Sudoku game built in webAssembly as my team's senior project at UNLV.
The game is unfinished, but it does showcase the ability to render fonts to an HTML5 canvas.
It uses the FreeType library in C++ and is compiled into wasm with Emscripten.

I compile on Windows, in the src directory, with the following command:
docker run --rm -v ${pwd}:/src ryanpoppe/unlvwebfonts em++ main.cpp Image.cpp Shape.cpp Text.cpp Cell.cpp -std=c++11 -O3 -s WASM=1 -s USE_FREETYPE=2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s ASSERTIONS=1 -s  LLD_REPORT_UNDEFINED -I/usr/local/include/freetype2 --preload-file assets -o index.html
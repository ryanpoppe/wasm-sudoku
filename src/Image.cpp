#include "Render.h"
#include "Image.h"

Image::Image(std::string path) {
	// Load image file into memory.
	file = SDL_RWFromFile(path.c_str(), "rb");
	if (!file) {
		std::cerr << "Image:Constructor:SDL_RWFromFile: " << SDL_GetError() << std::endl;
		// handle error
	}
	else {
		image = IMG_LoadPNG_RW(file);
		SDL_RWclose(file);
	}
}

Image::~Image() {
	// Remove image file from memory
	//if (file)
	//	SDL_RWclose(file);
	SDL_FreeSurface(image);
}

void Image::Stage(SDL_Surface* stage, int x, int y) {
	//image = IMG_LoadPNG_RW(file);
	if (!image) {
		std::cerr << "Image:Stage:IMG_LoadPNG_RW: " << IMG_GetError() << std::endl;
		// handle error
	}
	else {
		dest.w = image->w;
		dest.h = image->h;
		dest.x = x;
		dest.y = y;
		SDL_BlitSurface(image, nullptr, stage, &dest);
		//SDL_FreeSurface(image);
	}
	
}
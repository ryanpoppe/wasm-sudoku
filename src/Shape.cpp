#include <cstdint>
#include <string>
#include <iostream>
#include "Color.h"
#include "Render.h"
#include "Shape.h"

void Shape::Stage(SDL_Surface* stage, int x, int y) {
	// Might use this instead of having dest rect as private member
	// SDL_Rect dest = { x, y, width, height };
	dest.w = width;
	dest.h = height;
	dest.x = x;
	dest.y = y;
	SDL_FillRect(stage, &dest, SDL_MapRGBA(stage->format, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a));
}

Shape::Shape(unsigned short height, unsigned short width, const Color& color) {
	//std::cout << "Shape Constructor" << std::endl;
	this->height = height;
	this->width = width;
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	//std::cout << "Shape constructor: red: " << (int)r << " g: " << (int)g << " b: " << (int)b << " a: " << (int)a << std::endl;
}

Shape::~Shape() {
	//delete fill;
}
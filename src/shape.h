/**
  * \class Shape
  *
  * \ingroup Render
  *
  * \brief Creates shape objects to render to web canvas
  * 
  * Usage example:
  * 
  * @code
  * SDL_Surface* target;
  * Shape* square = new Shape(64, 64, Color::active());
  * square->Stage(target, 170, 170);
  * delete square;
  * square = nullptr;
  * @endcode
  *
  * \author Ryan Poppe
  *
  * \note Last update made by Ryan Poppe
  *
  * \version 1
  */

#ifndef H_Shape
#define H_Shape 

#include <cstdint>
#include <iostream>
#include <string>
#include <SDL.h>
#include "Render.h"
#include "Color.h"

class Shape : public Render {
private:
	unsigned short height; ///< Height of the rectangle object
	unsigned short width; ///< Width of the rectangle object
	unsigned short x; ///< x-coordinate
	unsigned short y; ///< y-coordinate
	SDL_Rect dest; ///< Controls location of the object on the canvas, with it's origin at the upper left.
	Color* fill; ///< The fill color of the Shape object
	uint8_t r; ///< Red RGBA value (0 <= r <= 255)
	uint8_t g; ///< Blue RGBA value (0 <= g <= 255)
	uint8_t b; ///< Red RGBA value (0 <= b <= 255)
	uint8_t a; ///< Alpha RGBA value (0 <= a <= 255). *This determines transparency
protected:

public:
	/** \brief Shape constructor
	*   \param height Height of shape in pixels
	*   \param width Width of shape in pixels
	*   \param color RGBA Color object
	*/
	Shape(unsigned short height, unsigned short width, const Color& color);
	/** \brief Shape destructor
	*   \note Deletes color object associated with this shape
	*/
	~Shape();
	/** \brief Add image to the rendering stage
	*   \param stage Pointer to the Stage SDL Surface
	*   \param x x-coordinate of where on the canvas to place the image
	*   \param y y-coordinate of where on the canvas to place the image
	*   \note Can be used to blit a transparent PNG
	*/
	void Stage(SDL_Surface* stage, int x, int y);
};

#endif
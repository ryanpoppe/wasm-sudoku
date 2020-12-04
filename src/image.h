/**
  * \class Image
  *
  * \ingroup Render
  *
  * \brief Creates image objects to render to web canvas
  * 
  * Usage example:
  * 
  * @code
  * SDL_Surface* target;
  * Image* bg;
  * // Load PNG assets
  * bg = new Image("assets/bg.png");
  * if (!bg) {
  *		std::cerr << "Failed to load background image." << std::endl;
  * }
  * // Draw background image
  * bg->Stage(target, 0, 0);
  * @endcode
  *
  * \author Ryan Poppe
  *
  * \note Last update made by Ryan Poppe
  *
  * \version 1
  */

#ifndef H_Image
#define H_Image 

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Render.h"

class Image : public Render {
//class Image {
private:
	SDL_Surface* image; ///< Pointer to the surface holding the image object.
	SDL_RWops* file; ///< Pointer to the image file in memory.
	SDL_Rect dest; ///< Controls location of the object on the canvas, with it's origin at the upper left.
protected:

public:
	/** \brief Image Constructor
	*   \param path The path to the image, including the filename and extension.
	*   \note e.g. assets/images/img.png
	*/
	Image(std::string path);

	/** \brief Image DeConstructor flushes the loaded image file from memory
	*/
	~Image();

	/** \brief Add image to the rendering stage
	*   \param stage Pointer to the Stage SDL Surface
	*   \param x x-coordinate of where on the canvas to place the image
	*   \param y y-coordinate of where on the canvas to place the image
	*   \note Can be used to blit a transparent PNG
	*/
	void Stage(SDL_Surface*, int, int);
};

#endif
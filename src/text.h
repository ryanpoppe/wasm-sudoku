/**
  * \class Text
  *
  * \ingroup Render
  *
  * \brief Creates text objects to render to web canvas
  *
  * Usage example:
  * 
  * @code
  * FT_Library ftLib;
  * FT_Face arial;
  * FT_Init_FreeType(&ftLib);
  * 
  * FT_New_Face(ftLib, "assets/arial.ttf", 0, &arial);
  * 
  * Text* message = new Text("Rich text example.", arial, 12);
  * message->Fill(Color(102, 204, 255));
  * message->Stroke(1, Color::invalid());
  * message->Stage(target, 0, 0);
  * 
  * delete message;
  * message = nullptr;
  * @endcode
  * 
  * \author Ryan Poppe
  *
  * \note Last update made by Ryan Poppe
  *
  * \version 1
  */

#ifndef H_Text
#define H_Text

#include <iostream>
#include <cstdint>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_OUTLINE_H

#include <SDL.h>

#include "Color.h"
#include "Render.h"

class Text : public Render {
private:
	char* text; ///< Character array that holds the text to be displayed
	int textLength; ///< Length of the text in the char array
	unsigned short strokeWidth; ///< Size of the the text stroke effect (outline of the text) in pixels.
	unsigned short fontSize; ///< Font size of the text to be rendered
	SDL_Rect dest; ///< Controls location of the object on the canvas, with it's origin at the upper left.
	FT_Library ftLib; ///< Used to initialize FreeType library
	FT_Face ftFace; ///< Stores the font face for FreeType
	const Color* fill; ///< Color of the text to be rendered
	Color* stroke; ///< Outline color of the text to be rendered.
	bool stroked; ///< True if text has outline
	//enum Align { left, center, right } alignment;
	/** \brief Draw a single FreeType bitmap glyph
	*   \param bm Accepts FreeType bitmap glyph
	*   \param x x-coordinate of where on the canvas to place the image
	*   \param y y-coordinate of where on the canvas to place the image
	*   \param stage pointer to the staging SDL_Surface
	*   \note Used by the stage function
	*/
	void DrawBitmap(FT_Bitmap, int, int, SDL_Surface*);
	uint8_t r; ///< Red RGBA value (0 <= r <= 255)
	uint8_t g; ///< Blue RGBA value (0 <= g <= 255)
	uint8_t b; ///< Red RGBA value (0 <= b <= 255)
	uint8_t a; ///< Alpha RGBA value (0 <= a <= 255). *This determines transparency
protected:

public:
	/** \brief Chnages the text color
	*   \param color RGBA color object
	*   \note Can be used to update the text color outside of the constructor
	*/
	void Fill(const Color& color);
	/** \brief Renders object to the stage
	*   \param stage pointer to the staging SDL_Surface
	*   \param x x-coordinate of where on the canvas to place the image
	*   \param y y-coordinate of where on the canvas to place the image
	*/
	void Stage(SDL_Surface* stage, int x, int y);
	/** \brief Set the text stroke (outline) color and thickness
	*   \param size Thickness of the text stroke
	*   \param color RGBA color object
	*   \note Function NOT implemented
	*/
	void Stroke(unsigned short size, const Color& color);
	/** \brief Text object Constructor
	*   \param message Text string to be rasterized
	*   \param fontPath Path of the TTF font file
	*   \param fontSize Point size of the text to be rasterized
	*   \param fill RGBA color object for the text color
	*/
	Text(const std::string& message, const std::string& fontPath, unsigned short fontSize, const Color& fill);
	~Text();
};

#endif
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_OUTLINE_H

#include <SDL.h>

#include "Color.h"
#include "Render.h"
#include "text.h"

Text::Text(const std::string& message, 
            const std::string& fontPath, 
            unsigned short fontSize,
            const Color& fillColor)
{
    int error;

    // Initialize FreeType
    error = FT_Init_FreeType(&ftLib);
    if (error) {
        std::cerr << "Error initializing FreeType" << std::endl;
    }

    // Load arial font
    error = FT_New_Face(ftLib, fontPath.c_str(), 0, &ftFace);
    if (error == FT_Err_Unknown_File_Format) {
        std::cerr << "Font format is unsupported" << std::endl;
    }
    else if (error) {
        std::cerr << "Font file is missing or corrupted" << std::endl;
    }
    this->fontSize = fontSize;

    FT_Set_Char_Size(ftFace, 0, 72 * fontSize, 72, 72); // 0 for char_width means same as char_height

    r = fillColor.r;
    g = fillColor.g;
    b = fillColor.b;
    a = fillColor.a;

	strokeWidth = 0;
	//this->fill = &fill;
	stroked = false;
    stroke = nullptr;
	
	//alignment = horizontal;

    text = nullptr;
    // Move text string into character array
    if (message.length() > 0) {
        textLength = message.length() + 1;
        text = new char[textLength]; // Length of message plus null terminator for c-string
        // Copy string into char array
        strcpy(text, message.c_str());
        //std::cout << "Initialize Text: '" << message << "'" << std::endl;
        //std::cout << "String Length: " << message.length() << std::endl;
        //std::cout << "Text Length: " << textLength << std::endl;
    }
    else {
        // Create null terminated string '?' to denote error
        textLength = 2;
        text = new char[textLength];
        text[0] = 63; // ASCII 63 == ?
        text[1] = 0;  // ASCII  0 == NULL
    }

}

Text::~Text() {
    // Deinitialize FreeType
    FT_Done_Face(ftFace);
    FT_Done_FreeType(ftLib);

	// Delete any outstanding dynamically allocated memory here

    delete text;
}

void Text::Stage(SDL_Surface* stage, int x, int y) {

    for (int n = 0; n < textLength - 1; n++)
    {
        FT_Load_Char(ftFace, text[n], FT_LOAD_RENDER);

        DrawBitmap(ftFace->glyph->bitmap, x + ftFace->glyph->bitmap_left, y - ftFace->glyph->bitmap_top, stage);

        x += ftFace->glyph->advance.x >> 6;
        y += ftFace->glyph->advance.y >> 6;
    }
}

void Text::Fill(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

void Text::Stroke(unsigned short width, const Color& color) {
	//stroke = &color;
	strokeWidth = width;
	//stroked = true;
}

void Text::DrawBitmap(FT_Bitmap bm, int x, int y, SDL_Surface* stage)
{
    if (bm.width == 0 || bm.rows == 0)
    {
        return;
    }

    std::vector< unsigned char > rgba(bm.width * bm.rows * 4);
    for (unsigned int y = 0; y < bm.rows; ++y)
    {
        for (unsigned int x = 0; x < bm.width; ++x)
        {
            unsigned char val = bm.buffer[(bm.pitch * y) + x];
            size_t base = ((bm.width * y) + x) * 4;
            rgba[base + 0] = r;
            rgba[base + 1] = g;
            rgba[base + 2] = b;
            rgba[base + 3] = val;
        }
    }

    SDL_Surface* glyph = SDL_CreateRGBSurfaceFrom
    (
        &rgba[0],
        bm.width,
        bm.rows,
        32,
        bm.width * 4,
        0x000000ff,
        0x0000ff00,
        0x00ff0000,
        0xff000000
    );

    SDL_SetSurfaceBlendMode(glyph, SDL_BlendMode::SDL_BLENDMODE_BLEND);
    SDL_Rect dest = { x, y, 0, 0 };
    SDL_BlitSurface(glyph, nullptr, stage, &dest);
    SDL_FreeSurface(glyph);
}
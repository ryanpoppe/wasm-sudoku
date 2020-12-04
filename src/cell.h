/** \defgroup Sudoku Web based Sudoku game using FreeType
 *
 * \brief Sudoku Game
 */

/**
 * \class Cell
 *
 * \ingroup Sudoku
 *
 * \brief Cell objects make up the 9x9 Sudoku grid. Each Cell is 64x64 pixels
 * 
 * Usage example:
 * 
 * @code
 * 
 * @endcode
 *
 * \author Ryan Poppe
 *
 * \version 1
 */

#ifndef H_Cell
#define H_Cell

#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <sstream>
#include "Color.h"
#include "Render.h"
#include "Shape.h"
#include "Text.h"

class Cell {
	private:
		bool active; ///< If this Cell is the currently active one on the game board
		bool highlighted; ///< Is part of the currently highlighted row, column, or block
		bool given; ///< Is an original given value at the start of the game
		bool invalid; ///< Cell currently holds an invalid value
		bool hidden; ///< Cell is currently hidden (e.g. game paused)
		bool hovered; ///< Mouse pointer currently sits within this Cell's coordinates
		bool entered; ///< Valid value has been entered in Cell
		unsigned short value; ///< value of the Cell on the board (1 <= value <= 9)
		unsigned short x; ///< x-coordiante on the Sudoku board (domain: 1 <= x <= 9)
		unsigned short y; ///< y-coordinate on the Sudoku board (range:  1 <= y <= 9)
		FT_Face font; ///< FreeType font face (TTF font pre-loaded in main, passed by reference)
		Color cellColor = Color::transparent(); ///< Object that holds pre-assigned color values for Cell objects
		Color textColor = Color::transparent(); ///< Object that holds pre-assigned color values for Cell objects
		Shape* square; ///< Shape object drawn on canvas
		Text* cellValue; ///< Text object drawn on canvas
		const unsigned short HEIGHT = 64; ///< Cell height in pixels
		const unsigned short WIDTH = 64; ///< Cell width in pixels
		SDL_Surface* target;
		/** \brief This method sets the colors of the Cell square and number
		*/
		void setColor();
	protected:
		
	public:
		/** \brief This method returns True if Cell is currently selected by the user
		*   \return active
		*/
		bool isActive() { return active; }
		/** \brief This method sets active status to this Cell
		*   \param active True to set this Cell as active
		*   \note Must set previously active Cell to false as well
		*/
		void setActive(bool active) { this->active = active; }
		/** \brief This method returns True if Cell is currently highlighted as part of the active group
		*   \return active
		*/
		bool isHighlighted() { return highlighted; }
		/** \brief This method sets highlighted status to this Cell
		*   \param highlighted True to set this Cell as highlighted
		*/
		void setHighlighted(bool highlighted) { this->highlighted = highlighted; }
		/** \brief This method returns True if Cell is an original given value
		*   \return given
		*/
		bool isGiven() { return given; }
		/** \brief This method sets given status to this Cell
		*   \param given True to set this Cell as given
		*/
		void setGiven(bool given) { this->given = given; }
		/** \brief This method returns True if Cell has an invalid value
		*   \return invalid
		*/
		bool isInvalid() { return invalid; }
		/** \brief This method sets invalid status to this Cell
		*   \param invalid True to set this Cell as invalid
		*/
		void setInvalid(bool invalid) { this->invalid = invalid; }
		/** \brief This method returns True if Cell is hidden
		*   \return hidden
		*/
		bool isHidden() { return hidden; }
		/** \brief This method sets hidden status to this Cell
		*   \param hidden True to set this Cell as hidden
		*/
		void setHidden(bool hidden) { this->hidden = hidden; }
		/** \brief This method returns True if mouse pointer is over this Cell
		*   \return hovered
		*/
		bool isHovered() { return hovered; }
		/** \brief This method sets hovered status to this Cell
		*   \param hovered True to set this Cell as hovered
		*/
		void setHovered(bool hovered) { this->hovered = hovered; }
		/** \brief This method returns True if a valid value has been entered in the Cell
		*   \return entered
		*/
		bool isEntered() { return entered; }
		/** \brief This method returns value of the Cell
		*   \return unsigned short value
		*/
		unsigned short getValue() { return value; }
		/** \brief This method sets the value of the Cell
		*   \param value unsigned short (1 <= value <=9)
		*/
		void setValue(unsigned short);
		/** \brief This method returns x-coordinate of the Cell
		*   \return unsigned short x-coordinate of the Cell on the game board
		*/
		unsigned short get_grid_pos_x() { return x; }
		/** \brief This method returns y-coordinate of the Cell
		*   \return unsigned short y-coordinate of the Cell on the game board
		*/
		unsigned short get_grid_pos_y() { return y; }
		/** \brief Draws the cell object onto the canvas.
		*/
		void Draw();
		/** \brief Set the (x,y) coordinate
		*   \param x unsigned short
		*   \param y unsigned short
		*/
		void setCoordinates(unsigned short x, unsigned short y) { this->x = x; this->y = y; }
		/** \brief Cell Constructor
		*   \param value unsigned short
		*   \param grid_pos_x unsigned short
		*   \param grid_pos_y unsigned short
		*   \param given bool
		*/
		Cell(SDL_Surface*, unsigned short, unsigned short, unsigned short, bool);
		/** \brief Cell Default Constructor
		*/
		Cell();
		/** \brief Cell DeConstructor
		*/
		~Cell();
};

#endif
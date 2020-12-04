#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <sstream>
#include "Color.h"
#include "Render.h"
#include "Shape.h"
#include "Text.h"
#include "Cell.h"

Cell::Cell(SDL_Surface* target,
			unsigned short value,
			unsigned short grid_pos_x,
			unsigned short grid_pos_y,
			bool given) {
				
	active = false;
	highlighted = false;
	invalid = false;
	hidden = false;
	hovered = false;
	entered = false;
	this->given = given;
	this->value = value;
	x = grid_pos_x;
	y = grid_pos_y;
	square = nullptr;
	cellValue = nullptr;
	this->target = target;
}

Cell::Cell() {
	active = false;
	highlighted = false;
	invalid = false;
	hidden = false;
	hovered = false;
	entered = false;
	given = false;
}
Cell::~Cell() {
	// Delete all dynamically allocated memory here
}

void Cell::setValue(unsigned short value) {
	if (!given) {
		if (value > 9 || value == 0) {
			std::cerr << "Cell value can only be a natural number 1-9" << std::endl;
		} else {
			this->value = value;
		}
	} else {
		std::cerr << "Cannot change value of given cell" << std::endl;
	}
}

void Cell::Draw() {
	// Set colors
	setColor();
	// Draw square
	if (cellColor != Color::transparent()) {
		square = new Shape(HEIGHT, WIDTH, cellColor);
		square->Stage(target, x, y);
		delete square;
		square = nullptr;
	}
	// Rasterize text for cell value
	if (isGiven() || isEntered()) {
		std::ostringstream ss;
		ss << value;
		cellValue = new Text(ss.str(), "assets/arial.ttf", 24, textColor);
		cellValue->Stage(target, x, y); // Offset x & y coordinates to center number in cell
		delete cellValue;
		cellValue = nullptr;
	}
}

void Cell::setColor() {
	/*
	* Set cell and text color based on status of cell
	*/

	// Case 1: Hidden cell (game paused)
	if (hidden) {
		cellColor = Color(Color::transparent());
		textColor = Color(Color::transparent());
	}
	else {
		// Case 2: Invalid number in cell
		if (invalid) {
			cellColor = Color::invalid();
			if (given) {
				textColor = Color::givenText();
			}
			else {
				textColor = Color::invalidText();
			}
		}
		else {
			// Case 3: Cell has been clicked on and is active
			if (active) { // !hidden, !invalid, active
				cellColor = Color::active();
				if (given) {
					textColor = Color::givenText();
				}
				else {
					textColor = Color::enteredText();
				}
			}
			else {
				//Case 4: Cell belongs to the group of the currently active cell
				if (highlighted) {
					cellColor = Color::highlighted();
					if (given) {
						textColor = Color::givenText();
					}
					else {
						textColor = Color::enteredText();
					}
				}
				else {
					// Case 5: Mouse pointer is currently over this cell
					if (hovered) {
						cellColor = Color::hovered();
						if (given) {
							textColor = Color::givenText();
						}
						else {
							textColor = Color::enteredText();
						}
					}
					else {
						cellColor = Color::transparent();
						if (given) {
							textColor = Color::givenText();
						}
						else {
							textColor = Color::enteredText();
						}
					}
				}
			}
		}
	}
}
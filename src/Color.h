/**
  * \class Color
  *
  * \ingroup Render
  *
  * \brief Creates RGBA color object
  * 
  * Usage example:
  * 
  * @code
  * void useColorClass(const Color& color)
  * {
  *		// Do something with the color
  *      uint8_t red = color->r;
  * }
  * useColorClass(Color::transparent());
  * useColorClass(Color::Color(255, 128, 0, 0));
  * @endcode
  * 
  * \author Ryan Poppe. Credit for constructor to stackoverfow
  *
  * \note Last update made by Ryan Poppe.
  * \version 1
  */

#ifndef H_Color
#define H_Color

#include <cstdint>

class Color
{
public:
	/** \brief Transparent background for cell.
	*
	* Alpha value is 0 so it will appear to be blank
	*/
	static constexpr Color transparent() { return Color(0, 0, 0, 0); }
	/** \brief Background color of active cell.
	*
	* Light blue
	*/
	static constexpr Color active() { return Color(187, 222, 251); }
	/** \brief Background color of highlighted cell.
	*
	* Grey
	*/
	static constexpr Color highlighted() { return Color(226, 231, 237); }
	/** \brief Background color of the cell the mouse pointer is currently touching.
	*
	* Lighter blue
	*/
	static constexpr Color hovered() { return Color(221, 238, 255); }
	/** \brief Text color of a cell that has a correct value entered by the player.
	*
	* Blue
	*/
	static constexpr Color enteredText() { return Color(74, 144, 226); }
	/** \brief Text color of a cell that has a value that was given at the start
	*
	* Black
	*/
	static constexpr Color givenText() { return Color(255, 255, 255); }
	/** \brief Background color of all cells with the same number as the active cell.
	*
	* Blueish
	*/
	static constexpr Color similar() { return Color(203, 219, 237); }
	/** \brief Background color of a cell containing a possible error.
	*
	* Pink
	*/
	static constexpr Color invalid() { return Color(247, 207, 214); }
	/** \brief Text color of a cell containing an incorrect number.
	*
	* Red
	*/
	static constexpr Color invalidText() { return Color(251, 61, 63); }
	/** \brief Constructor with default alpha value as 255
	*/
	constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
		: r(r), g(g), b(b), a(a)
	{}
	uint8_t r; ///< Red RGBA value (0 <= r <= 255)
	uint8_t g; ///< Blue RGBA value (0 <= g <= 255)
	uint8_t b; ///< Red RGBA value (0 <= b <= 255)
	uint8_t a; ///< Alpha RGBA value (0 <= a <= 255). *This determines transparency
	/** \brief Overloaded equality operator
	*   \param c RHS Color object
	*/
	bool operator==(const Color& c) const { return (c.r == r && c.g == g && c.b == b && c.a == a); }
	/** \brief Overloaded inequality operator
	*   \param c RHS Color object
	*/
	bool operator!=(const Color& c) const { return (c.r != r && c.g != g && c.b != b && c.a != a); }
};

#endif
/** \defgroup Render Game Rendering Engine
 *
 * \brief Game rendering engine class to develop C++ games for webAssembly
 */

 /**
  * \class Render
  *
  * \ingroup Render
  *
  * \brief Renders objects to web canvas
  *
  * \author Ryan Poppe
  *
  * \note Last update made by Ryan Poppe
  * 
  * \version 1
  */

#ifndef H_Render
#define H_Render

#include <SDL.h>
#include <SDL_image.h>

class Render {
public:
	virtual void Stage(SDL_Surface*, int, int) = 0;
};

#endif
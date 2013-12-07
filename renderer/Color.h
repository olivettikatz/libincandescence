/* Copyright 2013 Oliver Katz
 *
 * This file is part of LibIncandescence.
 *
 * LibIncandescence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LibIncandescene is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibIncandescence.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file Color.h
 *  \brief Drawable subclass for rendering colors. */

#ifndef __LIB_INCANDESCENCE_COLOR_H
#define __LIB_INCANDESCENCE_COLOR_H

#include "Drawable.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! \brief Drawable subclass for rendering colors. */
	class Color : public Drawable
	{
	public:
		/*! Red, green, blue, and alpha channels (0-255). */
		unsigned char r, g, b, a;

		/*! Constructor. */
		Color() : r(0), g(0), b(0), a(255) {requireVersion(1, 4);}

		/*! Constructor. */
		Color(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b), a(255) {requireVersion(1, 4);}

		/*! Constructor. */
		Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {requireVersion(1, 4);}

		/*! Render to window (OpenGL 1-2 only). */
		void renderHandler(Window &w);

		/*! Render to GLSL attribute (OpenGL 3-4 only). */
		void renderHandler(GLint so);
	};
}

#endif
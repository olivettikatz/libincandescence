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

/*! \file Text.h
 *  \brief Drawable subclass for drawing text with FontRenderer (see FontRenderer.h). */

#ifndef __LIB_INCANDESCENCE_TEXT_H
#define __LIB_INCANDESCENCE_TEXT_H

#include "Drawable.h"
#include "Color.h"
#include "../font/FontRenderer.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! \brief Drawable subclass for drawing text.
	 *  Contains a location, color, the text to render, and a reference to the font to use. */
	class Text : public Drawable
	{
	protected:
		GLint uniformColor;

	public:
		/*! Pixel coordinates to render at. */
		int x, y;

		/*! Color to render in. */
		Color color;

		/*! Text to render. */
		string text;

		/*! Font to render in. */
		FontRenderer *font;

		/*! Constructor. */
		Text() : x(0), y(0), font(NULL) {requireVersion(1, 4);}

		/*! Constructor.
		 *  \param t Text to render.
		 *  \param _x X pixel coordinate.
		 *  \param _y Y pixel coordinate.
		 *  \param f FontRenderer to use. */
		Text(string t, int _x, int _y, FontRenderer &f) : x(_x), y(_y), text(t), font(&f) {requireVersion(1, 4);}

		/*! Loads text textures. */
		void loadHandler(Window &w);

		/*! Renders text. */
		void renderHandler(Window &w);
	};
}

#endif
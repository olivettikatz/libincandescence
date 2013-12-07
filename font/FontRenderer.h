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

 /*! \file FontRenderer.h
  *  \brief Class for rendering fonts to OpenGL context.
  *  Supports OpenGL 1-4. Uses FTGL for 1-2 and the FreeType library for 3-4. Automatically detects current OpenGL
  *  version (see GLUtil.h). */

#ifndef __LIB_INCANDESCENCE_FONT_RENDERER_H
#define __LIB_INCANDESCENCE_FONT_RENDERER_H

#include "../util/Util.h"
#include "../util/GLUtil.h"
#include "../renderer/Poly.h"
#include <FTGL/ftgl.h>
#include <FTGL/FTFont.h>

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;
	using namespace FTGL;

	/*! Initially false, set to true once FreeType library has been initialized. Prevents it from being initialized 
	 * twice. */
	extern bool hasFTBeenInitialized;

	/*! FreeType specific variable. */
	extern FT_Library ftlib;

	/*! Initializes font rendering (FTGL/FreeType).
	 * \warning Must be called before any FontRenderer calls can be made, otherwise they have undefined behavior. */
	void initFontRendering();

	class Window;

	/*! Class for rendering font to current OpenGL context. */
	class FontRenderer
	{
	protected:
		string path;
		int dpi;
		int width, height;
		FTFont *font;
		FT_Face face;
		bool rastering;

		GLint uniformTex, attrCoord;
		GLuint vbo;

		void postLoad(Window &w);

	public:
		/*! Constructor. */
		FontRenderer() : dpi(72), width(5), height(12), font(NULL), rastering(true), vbo(0) {}

		/*! Constructure.
		 *  \param p Path to font file.
		 *  \param h Height of font in pixels.
		 *  \param w Width of fixed-width font. */
		FontRenderer(string p, int h, int w = -1) : path(p), dpi(72), width(w), height(h), font(NULL), rastering(true), vbo(0) {if (width == -1) width = height/2;}

		/*! Sets the DPI of the screen to use for font (72 by default). */
		void setDPI(int d);

		/*! Gets FreeType font object (OpenGL 3-4 only). */
		FTFont *getFont();

		/*! Loads 2D font (OpenGL 1-2 only). */
		void load2D(Window &w);

		/*! Loads 3D font. */
		void load3D(Window &w);

		/*! Loads 3D outline font (OpenGL 1-2 only). */
		void load3DOutline(Window &w, int outline = -1);

		/*! Loads 3D extrude font (OpenGL 1-2 only). */
		void load3DExtrude(Window &w, int extrude = -1);

		/*! Unloads font. */
		void unload();

		/*! Returns true if font can be rendered. */
		bool good();

		/*! Renders text to window at x,y pixel coordinates. */
		void render(Window &w, string text, int x, int y);

		/*! Returns the width of text if it were to be rendered in pixels. */
		int getWidth(string text);
	};
}

#endif
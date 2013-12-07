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

/*! \file Drawable.h
 *  \brief Base class for all things that can be drawn on an OpenGL context. */

#ifndef __LIB_INCANDESCENCE_DRAWABLE_H
#define __LIB_INCANDESCENCE_DRAWABLE_H

#include "../util/Util.h"
#include "../util/GLUtil.h"

/*! \def INCD_REPORT_UNSUPPORTED_GL_VERSION()
 *  \warning Can ONLY be used within methods of a subclass of Drawable. */
#define INCD_REPORT_UNSUPPORTED_GL_VERSION() reportUnsupportedGLVersion(__FILE__,__LINE__)

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	class Window;

	/*! \brief Base class of drawable things.
	 *  When creating a subclass of Drawable, the good method must be substantiaed. If your subclass needs to be loaded before it is rendered,
	 *  put that code in loadHandler. If your subclass needs to be rendered to a window, put that in renderHandler(Window &w). If your subclass
	 *  needs to be rendered to a GLSL attribute, put that in renderHandler(GLint so). For example: \include Drawable.example */
	class Drawable
	{
	protected:
		int minVersion, maxVersion;

		/*! Sets minimum and maximum supported OpenGL versions for Drawable subclass. This method must be called before Drawable::load is called,
		 *  otherwise a fatal error will be triggered. */
		void requireVersion(int min, int max);

		/*! Helper method for INCD_REPORT_UNSUPPORTED_GL_VERSION(). */
		void reportUnsupportedGLVersion(string file, int linenum);

	public:
		/*! Drawing mode for vertex vector data. */
		typedef enum
		{
			Points = GL_POINTS,
			SeparateLines = GL_LINES,
			ConnectedLines = GL_LINE_STRIP,
			StrokedPoly = GL_LINE_LOOP,
			SeparateTriangles = GL_TRIANGLES,
			ConnectedTriangles = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN,
			SeparateQuads = GL_QUADS,
			ConnectedQuads = GL_QUAD_STRIP,
			FilledPoly = GL_POLYGON
		} DrawingMode;

		/*! Constructor. */
		Drawable() : minVersion(-1), maxVersion(-1) {}

		/*! Returns true if object can be rendered. */
		virtual bool good();

		/*! Loads object for window. */
		void load(Window &w);

		/*! Virtual method to load the object for window. */
		virtual void loadHandler(Window &w);

		/*! Renders object in window. */
		void render(Window &w);

		/*! Virtual method to render the object for window. */
		virtual void renderHandler(Window &w);

		/*! Renders object to GLSL attribute. */
		void render(GLint so);

		/*! Virtual method to render the object to GLSL attribute. 
		 *  \warning OpenGL >=3 only. */
		virtual void renderHandler(GLint so);
	};
}

#endif
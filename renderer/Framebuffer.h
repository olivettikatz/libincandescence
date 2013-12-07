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

/*! \file Framebuffer.h
 *  \brief Drawable subclass to handler post-processing framebuffers. 
 *  \warning THIS DOESN'T WORK YET. */

#ifndef __LIB_INCANDESCENCE_FRAMEBUFFER_H
#define __LIB_INCANDESCENCE_FRAMEBUFFER_H

#include "../util/GLUtil.h"
#include "Drawable.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Dude, this doesn't work, what did I tell you?!
	 *  \warning If this did work, it would only work for OpenGL 3-4. */
	class Framebuffer : public Drawable
	{
	protected:
		GLuint fbo, fboTexture, rboDepth, vboFboVerts;
		GLint attribCoord, uniformTexture;

	public:
		/*! Constructor. */
		Framebuffer() : fbo(0), fboTexture(0), rboDepth(0), attribCoord(-1), uniformTexture(-1) {requireVersion(3, 4);}

		/*! Load for window. */
		void loadHandler(Window &w);

		/*! Render to window. */
		void renderHandler(Window &w);

		/*! Resize framebuffer. */
		void resize(int w, int h);

		/*! Begin rendering to framebuffer. */
		void use(Window &w);

		/*! Stop rendering to framebuffer and go back to rendering to the OpenGL context. */
		void unuse();
	};
}

#endif
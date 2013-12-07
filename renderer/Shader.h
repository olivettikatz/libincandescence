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

/*! \file Shader.h
 *  \brief Class for handling GLSL shaders. */

#ifndef __LIB_INCANDESCENCE_SHADER_H
#define __LIB_INCANDESCENCE_SHADER_H

#include "../util/GLUtil.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Class for handling GLSL shaders (OpenGL 3-4). */
	class Shader
	{
	protected:
		string vertPath, fragPath;
		GLuint pid;

	public:
		/*! Constructor.
		 *  \param v Path of vertex shader GLSL script.
		 *  \param f Path of fragment shader GLSL script */
		Shader(string v = "", string f = "") : vertPath(v), fragPath(f), pid(0) {}

		/*! Constructor from GL program ID. */
		Shader(GLuint p) : pid(p) {}

		/*! Gets GL program ID from linked shaders. */
		GLuint getPid();

		/*! Returns true if GL program is linked correctly and usable. */
		bool good();

		/*! Sets path of vertex shader GLSL script to use. */
		void useVertexScript(string v);

		/*! Sets path of fragment shader GLSL script to use. */
		void useFragmentScript(string f);

		/*! Sets path of both shader GLSL scripts to use. */
		void useScripts(string v, string f);

		/*! Loads both shader GLSL scripts and links GL program. */
		void load();

		/*! Unloads GL program.
		 *  \warning THIS DOESN'T WORK YET */
		void unload();

		/*! Uses GL program for shading in current OpenGL context. */
		void use();

		/*! Gets GLSL attribute with name. */
		GLint getAttribute(string s);

		/*! Gets GLSL uniform with name. */
		GLint getUniform(string s);
	};
}

#endif
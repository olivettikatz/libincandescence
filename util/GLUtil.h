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

/*! \file GLUtil.h
 *  \brief Basic utilities for OpenGL
 *  Contains macros for checking for errors outputted by OpenGL and for the current version of OpenGL being used.
 *  Has methods for initializing and halting OpenGL, GLFW, and GLEW. Handles execution time, display DPI, conversion
 *  between window pixel coordinates and OpenGL coordinates, and the loading of GLSL shaders. */

/*! \def INCD_GL_ERROR()
 *  \brief Checks for OpenGL standard errors and framebuffer errors.
 *  Displays any errors, if found.
 *  \returns True if there are any errors, false otherwise. */

/*! \def INCD_GL_FRAMEBUFFER_ERROR()
 *  \brief Checks for OpenGL framebuffer errors only.
 *  Displays any errors, if found.
 *  \returns True if there are any errors, false otherwise. */

/*! \def INCD_GL_VERSION_MAJOR
 *  \brief The value of the major version of OpenGL. */

/*! \def INCD_GL_VERSION_MINOR
 *  \brief The value of the minor version of OpenGL. */

/*! \def INCD_GL_VERSION_ERROR()
 *  \brief Displays error for unsupported instruction in the current OpenGL version. */

#ifndef __LIB_INCANDESCENCE_GL_UTIL_H
#define __LIB_INCANDESCENCE_GL_UTIL_H

#include "Util.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTFont.h>

#define INCD_GL_ERROR() (incandescence::getGLError(__FILE__,__LINE__)||incandescence::getGLFramebufferError(__FILE__,__LINE__))
#define INCD_GL_FRAMEBUFFER_ERROR() incandescence::getGLFramebufferError(__FILE__,__LINE__)
#define INCD_GL_VERSION_MAJOR incandescence::glMajorVersion
#define INCD_GL_VERSION_MINOR incandescence::glMinorVersion

#define INCD_GL_VERSION_ERROR() INCD_ERROR("unsupported instruction for OpenGL version " << INCD_GL_VERSION_MAJOR << "." << INCD_GL_VERSION_MINOR)

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! The integer values of the major and minor versions of OpenGL (initialized as soon as the first OpenGL
	 *  context is created [see Window.h]). */
	extern int glMajorVersion, glMinorVersion;

	/*! Initially false, is only set to true after a call to initGLEW. Is used to prevent GLEW-specific calls before
	 *  GLEW has been initialized. */
	extern bool hasGlewBeenInitialized;

	/*! Initially false, is only set to true after first context is created. Is used to prevent OpenGL error checking
	 *  before a context has been created. A bug exists where if this happens, instead of returning no error the function
	 *  causes a segfault. Confirmed on Mac OS X Mavaricks through LibIncandescence testing, so.... */
	extern bool hasContextBeenBound;

	/*! Initially false, is only set to true after first framebuffer is created. Is used to prevent OpenGL framebuffer
	 *  error checking before a framebuffer has been created. See comments for hasGlewBeenInitialized. */
	extern bool hasFramebufferBeenCreated;
	
	/*! \brief Initializes OpenGL.
	 *  \param maj Requested major version.
	 *  \param min Requested minor version.
	 *  \warning Must be called before any other LibIncandescence calls. LibIncandescence calls have undefined behavior before initGL. */
	void initGL(int maj = -1, int min = -1);

	/*! \brief Halts OpenGL.
	 *  Does not have to be called at the end of the program. Its purpose is to halt OpenGL in the middle of execution
	 *  for switching from a graphical interface back to a command line one (or none). */
	void haltGL();

	/*! \brief Initializes GLEW.
	 *  \warning Some LibIncandescence calls require GLEW and will have undefined behavior before this is called. */
	void initGLEW();

	/*! \brief Returns execution time in seconds. */
	double getTime();

	/*! \brief Sets execution time in seconds. */
	void setTime(double t = 0);

	/*! \brief Returns screen DPI.
	 *  \warning Detected through OpenGL. */
	int getDPI();

	/*! \brief Helper method for INCD_GL_ERROR. */
	bool getGLError(string file = "", int linenum = -1);

	/*! \brief Helper method for INCD_GL_FRAMEBUFFER_ERROR. */
	bool getGLFramebufferError(string file = "", int linenum = -1);

	/*! \brief Converts X pixel coordinate to OpenGL coordinate.
	 *  \param x Pixel coordinate
	 *  \param w Width of window */
	GLfloat pixelCoordXToGL(int x, int w);

	/*! \brief Converts Y pixel coordinate to OpenGL coordinate.
	 *  \param x Pixel coordinate
	 *  \param h Height of window */
	GLfloat pixelCoordYToGL(int y, int h);

	/*! \brief Loads GLSL shaders from files and returns OpenGL program ID for linked program using shaders.
	 *  \param vertexShaderPath path to vertex shader GLSL script.
	 *  \param fragmentShaderPath path to fragment shader GLSL script. */
	GLuint loadGLShaders(string vertexShaderPath, string fragmentShaderPath);
}

#endif
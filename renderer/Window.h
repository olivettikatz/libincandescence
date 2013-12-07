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

/*! \file Window.h
 *  \brief Base class for managing windows in LibIncandescence
 *  \warning If you use the Window class directly, nothing will happen. You have to create your own subclass to render things to the window.
 *  Contains GLFW window management wrapper stuff, too. */

/*! \def INCD_WINDOW_DEFAULT_WIDTH
 *  \brief Default width for a window in LibIncandescence (usually 200 pixels). */

/*! \def INCD_WINDOW_DEFAULT_HEIGHT
 *  \brief Default height for a window in LibIncandescence (usually 200 pixels). */

/*! \def INCD_WINDOW_DEFAULT_TITLE
 *  \brief Default title for a window in LibIncandescence (usually "LibIncandescence 0.01-ALPHA"). */

/*! \def INCD_SHADER_NAME_2D
 *  \brief Name of the 2D shader. */

/*! \def INCD_SHADER_NAME_3D
 *  \brief Name of the 3D shader. */

/*! \def INCD_SHADER_NAME_TEXT
 *  \brief Name of the text shader. */

/*! \def INCD_SHADER_NAME_POST_PROCESSING
 *  \brief Name of the 2D shader. */

/*! \def INCD_SHADER_2D
 *  \brief Index of the 2D shader. */

/*! \def INCD_SHADER_3D
 *  \brief Index of the 3D shader. */

/*! \def INCD_SHADER_TEXT
 *  \brief Index of the text shader. */

/*! \def INCD_SHADER_POST_PROCESSING
 *  \brief Index of the 2D shader. */

#ifndef __LIB_INCANDESCENCE_WINDOW_H
#define __LIB_INCANDESCENCE_WINDOW_H

#include "../util/Util.h"
#include "../util/GLUtil.h"
#include "ModifierStatus.h"
#include "Key.h"
#include "Shader.h"

#define INCD_WINDOW_DEFAULT_WIDTH 200
#define INCD_WINDOW_DEFAULT_HEIGHT 200
#define INCD_WINDOW_DEFAULT_TITLE "LibIncandescence 0.01-ALPHA"

#define INCD_SHADER_NAME_2D "Poly2D"
#define INCD_SHADER_NAME_3D "Poly3D"
#define INCD_SHADER_NAME_TEXT "Text"
#define INCD_SHADER_NAME_POST_PROCESSING "PostProcessing"

#define INCD_SHADER_2D 0
#define INCD_SHADER_3D 3
#define INCD_SHADER_TEXT 1
#define INCD_SHADER_POST_PROCESSING 2

namespace incandescence
{
	using namespace std;

	class Window;

	/*! Initially NULL, contains a reference to the current focused window as soon as the first window is created. */
	extern Window *focusedWindow;

	/*! Internal GLFW callback. */ 
	void _windowErrorHandler(int error, const char *desc);

	/*! Internal GLFW callback. */ 
	void _windowKeyHandler(GLFWwindow *window, int key, int scan, int act, int mods);

	/*! Internal GLFW callback. */ 
	void _windowMousePositionHandler(GLFWwindow *window, double x, double y);

	/*! Internal GLFW callback. */ 
	void _windowMouseButtonHandler(GLFWwindow *window, int button, int action, int mods);

	/*! Internal GLFW callback. */ 
	void _windowMouseScrollHandler(GLFWwindow *window, double dx, double dy);

	/*! \brief Base class for a LibIncandescence window.
	 *  Contains ability to manage window, organize shaders to use in window, and instantiatable virtual methods for implementing LibIncandescence windows. */
	class Window
	{
	protected:
		GLFWwindow *window;
		vector<pair<string, Shader> > shaders;
		int currentShader;

		int width, height;
		string title;

	public:
		/*! Constructor. */
		Window() : window(NULL), currentShader(-1), width(INCD_WINDOW_DEFAULT_WIDTH), height(INCD_WINDOW_DEFAULT_HEIGHT), title(INCD_WINDOW_DEFAULT_TITLE) {}
		
		/*! Sets size of the window (does not call resizeHandler directly). */
		void setSize(int w, int h);

		/*! Gets width of window. */
		int getWidth();

		/*! Gets height of window. */
		int getHeight();

		/*! Sets position of the window. */
		void setPosition(int x, int y);

		/*! Gets X position of window on screen. */
		int getX();

		/*! Gets Y position of window on screen. */
		int getY();

		/*! Sets the title of the window. */
		void setTitle(string t);

		/*! Gets the title of the window. */
		string getTitle();
		

		/*! Hides the window. */
		void hide();

		/*! Shows the window. */
		void show();

		/*! Minimizes the window. */
		void minimize();

		/*! Restores the window from minimization. */
		void restore();
		
		/*! Loads the OpenGL context of the window as the current OpenGL context. */
		void loadContext();

		/*! Initializes the window. */
		void init();

		/*! Checks if window is ready to be rendered to. */
		bool isReady();

		/*! Halts the window. */
		void halt();

		/*! Executes the event loop for the window. */
		void exec();

		/*! Loads the default shaders (which can be accessed with INCD_SHADER_*) */
		void loadDefaultShaders();

		/*! Checks if shader with index exists. */
		bool hasShader(int n);

		/*! Checks if shader with name exists. */
		bool hasShader(string n);

		/*! Loads a shader with name. */
		int loadShader(string n, Shader s);

		/*! Loads a shader with name from GLSL shader script paths. */
		int loadShader(string n, string v, string f);

		/*! Gets the index of a shader with name
		 *  \returns -1 if no shader with name exists. */
		int findShader(string n);

		/*! Gets a reference to the shader with an index. If no parameters are given, it returns a reference to the current shader. */
		Shader &getShader(int n = -1);

		/*! Gets a reference to the shader with a name. */
		Shader &getShader(string n);

		/*! Gets the index of the current shader. */
		int getCurrentShader();

		/*! Uses a shader with an index, sets the current shader index to \a n. */
		void useShader(int n);

		/*! Uses a shader with a name, sets the current shader index to the index of the shader with name \a n. */
		void useShader(string n);

		/*! Instantiatable callback for keyboard events. */
		virtual void keyHandler(Key &k, ModifierStatus &m, bool pressed);

		/*! Instantiatable callback for mouse button events. */
		virtual void buttonHandler(int b, ModifierStatus &m, bool pressed);

		/*! Instantiatable callback for mouse movement events. */
		virtual void mouseHandler(double x, double y);

		/*! Instantiatable callback for mouse scroll events. */
		virtual void scrollHandler(double x, double y);

		/*! Instantiatable callback for window resize events. */
		virtual void resizeHandler(int w, int h);

		/*! Instantiatable callback for loading the window (run during Window::init). */
		virtual void loadHandler();

		/*! Instantiatable callback for rendering the window (run multiple times during Window::exec). */
		virtual void renderHandler();
	};
}

#endif
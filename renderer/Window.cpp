#include "Window.h"

namespace incandescence
{
	Window *focusedWindow = NULL;

	void _windowErrorHandler(int error, const char *desc)
	{
		INCD_ERROR("GLFW error (" << error << "): " << desc);
	}

	void _windowKeyHandler(GLFWwindow *window, int key, int scan, int act, int mods)
	{
		ModifierStatus ms = ModifierStatus(mods);
		Key k = Key(key, ms.shift());
		if (focusedWindow != NULL)
		{
			if (act == GLFW_PRESS || act == GLFW_REPEAT)
				focusedWindow->keyHandler(k, ms, true);
			else if (act == GLFW_RELEASE)
				focusedWindow->keyHandler(k, ms, false);
		}
	}

	void _windowMousePositionHandler(GLFWwindow *window, double x, double y)
	{
		if (focusedWindow != NULL)
			focusedWindow->mouseHandler(x, y);
	}

	void _windowMouseButtonHandler(GLFWwindow *window, int button, int action, int mods)
	{
		ModifierStatus ms = ModifierStatus(mods);
		if (focusedWindow != NULL)
		{
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
				focusedWindow->buttonHandler(button+1, ms, true);
			else
				focusedWindow->buttonHandler(button+1, ms, false);
		}
	}

	void _windowMouseScrollHandler(GLFWwindow *window, double dx, double dy)
	{
		if (focusedWindow != NULL)
			focusedWindow->scrollHandler(dx, dy);
	}

	void Window::setSize(int w, int h)
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		width = w;
		height = h;
		glfwSetWindowSize(window, w, h);
	}

	int Window::getWidth()
	{
		return width;
	}

	int Window::getHeight()
	{
		return height;
	}

	void Window::setPosition(int x, int y)
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwSetWindowPos(window, x, y);
	}

	int Window::getX()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		return x;
	}

	int Window::getY()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		return y;
	}

	void Window::setTitle(string t)
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		title = t;
		glfwSetWindowTitle(window, t.c_str());
	}

	string Window::getTitle()
	{
		return title;
	}

	void Window::loadDefaultShaders()
	{
		loadShader(INCD_SHADER_NAME_2D, "VertexShader2D.glsl", "FragmentShader2D.glsl");
		loadShader(INCD_SHADER_NAME_TEXT, "VertexShaderText.glsl", "FragmentShaderText.glsl");
		loadShader(INCD_SHADER_NAME_POST_PROCESSING, "VertexShaderPostProcessing.glsl", "FragmentShaderPostProcessing.glsl");

		if (hasShader(INCD_SHADER_2D) == false)
			INCD_WARNING("running without shader (INCD_SHADER_2D).");
		if (hasShader(INCD_SHADER_TEXT) == false)
			INCD_WARNING("running without shader (INCD_SHADER_TEXT).");
		if (hasShader(INCD_SHADER_POST_PROCESSING) == false)
			INCD_WARNING("running without shader (INCD_SHADER_POST_PROCESSING).");
		if (hasShader(INCD_SHADER_3D) == false)
			INCD_WARNING("running without shader (INCD_SHADER_3D).");
	}

	bool Window::hasShader(int n)
	{
		return (n >= 0 && n < shaders.size());
	}

	bool Window::hasShader(string n)
	{
		return (findShader(n) >= 0);
	}

	int Window::loadShader(string n, Shader s)
	{
		pair<string, Shader> tmp;
		tmp.first = n;
		tmp.second = s;
		shaders.push_back(tmp);
		return (shaders.size()-1);
	}

	int Window::loadShader(string n, string v, string f)
	{
		Shader s = Shader(v, f);
		s.load();
		return loadShader(n, s);
	}

	int Window::findShader(string n)
	{
		for (vector<pair<string, Shader> >::iterator i = shaders.begin(); i != shaders.end(); i++)
		{
			if (i->first.compare(n) == 0)
			{
				return distance(shaders.begin(), i);
			}
		}

		return -1;
	}

	Shader &Window::getShader(int n)
	{
		if (n == -1)
			return shaders[currentShader].second;
		return shaders[n].second;
	}

	Shader &Window::getShader(string n)
	{
		return shaders[findShader(n)].second;
	}

	int Window::getCurrentShader()
	{
		return currentShader;
	}

	void Window::useShader(int n)
	{
		currentShader = n;
		shaders[n].second.use();
	}

	void Window::useShader(string n)
	{
		currentShader = findShader(n);
		shaders[currentShader].second.use();
	}

	void Window::show()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwShowWindow(window);
	}

	void Window::hide()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwHideWindow(window);
	}

	void Window::minimize()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwIconifyWindow(window);
	}

	void Window::restore()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwRestoreWindow(window);
	}

	void Window::loadContext()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwMakeContextCurrent(window);
		hasContextBeenBound = true;
	}

	void Window::init()
	{
		glfwSetErrorCallback(_windowErrorHandler);

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window)
		{
			haltGL();
			INCD_ERROR("unable to create window.");
		}

		loadContext();
		if (INCD_GL_ERROR())
			return ;

		initGLEW();
		if (INCD_GL_ERROR())
			return ;

		glfwSetKeyCallback(window, _windowKeyHandler);
		glfwSetMouseButtonCallback(window, _windowMouseButtonHandler);
		glfwSetCursorPosCallback(window, _windowMousePositionHandler);
		glfwSetScrollCallback(window, _windowMouseScrollHandler);
		focusedWindow = this;

		if (glMajorVersion == 0)
		{
			string s = string((const char *)glGetString(GL_VERSION));
			glMajorVersion = atoi(s.substr(0, s.find(".")).c_str());
			glMinorVersion = atoi(s.substr(s.find(".")+1, s.find(" ")).c_str());
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (INCD_GL_ERROR())
			return ;

		loadDefaultShaders();

		loadHandler();
	}

	bool Window::isReady()
	{
		return (window != NULL);
	}

	void Window::halt()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		glfwWindowShouldClose(window);
	}

	void Window::exec()
	{
		if (!isReady())
			INCD_ERROR("window is not ready yet.");
		if (INCD_GL_ERROR())
			return ;
		while (!glfwWindowShouldClose(window))
		{
			int tmpw, tmph;
			glfwGetWindowSize(window, &tmpw, &tmph);
			if (tmpw != width || tmph != height)
			{
				resizeHandler(tmpw, tmph);
				width = tmpw;
				height = tmph;
			}

			if (glMajorVersion <= 2)
			{
				glViewport(0, 0, width, height);
				if (INCD_GL_ERROR())
					return ;
				glClear(GL_COLOR_BUFFER_BIT);
				if (INCD_GL_ERROR())
					return ;
				glMatrixMode(GL_PROJECTION);
				if (INCD_GL_ERROR())
					return ;
				glLoadIdentity();
				if (INCD_GL_ERROR())
					return ;
				glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
				if (INCD_GL_ERROR())
					return ;
				glMatrixMode(GL_MODELVIEW);
				if (INCD_GL_ERROR())
					return ;
				glLoadIdentity();
				if (INCD_GL_ERROR())
					return ;
			}
			else if (glMajorVersion >= 3)
			{
				if (INCD_GL_ERROR())
					return ;
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				if (INCD_GL_ERROR())
					return ;
			}

			if (INCD_GL_ERROR())
			{
				INCD_WARNING("errors occured during render-time initialization.");
				return ;
			}

			renderHandler();
			if (INCD_GL_ERROR())
			{
				INCD_WARNING("errors occured during user's re-definition of 'renderHandler'.");
				return ;
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
	}

	void Window::keyHandler(Key &k, ModifierStatus &m, bool pressed)
	{
	}

	void Window::buttonHandler(int b, ModifierStatus &m, bool pressed)
	{
	}

	void Window::mouseHandler(double x, double y)
	{
	}

	void Window::scrollHandler(double x, double y)
	{
	}

	void Window::resizeHandler(int w, int h)
	{
	}

	void Window::loadHandler()
	{
	}

	void Window::renderHandler()
	{
	}
}

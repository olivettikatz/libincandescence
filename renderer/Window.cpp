#include "Window.h"

namespace incandescence
{
	void Window::setSize(int w, int h)
	{
		width = w;
		height = h;
	}

	int Window::getWidth()
	{
		return width;
	}

	int Window::getHeight()
	{
		return height;
	}

	void Window::setTitle(string t)
	{
		title = t;
	}

	string Window::getTitle()
	{
		return title;
	}

	void Window::loadContext()
	{
		glfwMakeContextCurrent(window);
	}

	void Window::init()
	{
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window)
		{
			Window::haltGlobal();
			INCD_ERROR("unable to create window.");
		}

		loadContext();
	}

	void Window::exec()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
}

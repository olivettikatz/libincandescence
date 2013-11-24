#ifndef __LIB_INCANDESCENCE_WINDOW_H
#define __LIB_INCANDESCENCE_WINDOW_H

#include "../util/Util.h"
#include <GLFW/glfw3.h>

#define INCD_WINDOW_DEFAULT_WIDTH 200
#define INCD_WINDOW_DEFAULT_HEIGHT 200
#define INCD_WINDOW_DEFAULT_TITLE "LibIncandescence 0.01-ALPHA"

namespace incandescence
{
	using namespace std;

	class Window
	{
	protected:
		GLFWwindow *window;

		int width, height;
		string title;

	public:
		Window() : window(NULL), width(INCD_WINDOW_DEFAULT_WIDTH), height(INCD_WINDOW_DEFAULT_HEIGHT), title(INCD_WINDOW_DEFAULT_TITLE) {}
		Window(const Window &w) : width(w.width), height(w.height), title(w.title) {}
		void setSize(int w, int h);
		int getWidth();
		int getHeight();
		void setTitle(string t);
		string getTitle();
		void loadContext();
		void init();
		void exec();

		static void initGlobal()
		{
			if (!glfwInit())
			{
				INCD_ERROR("could not initialize OpenGL.");
			}
		}

		static void haltGlobal()
		{
			glfwTerminate();
		}
	};
}

#endif
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

namespace incandescence
{
	using namespace std;

	class Window;

	extern Window *focusedWindow;
	void _windowErrorHandler(int error, const char *desc);
	void _windowKeyHandler(GLFWwindow *window, int key, int scan, int act, int mods);
	void _windowMousePositionHandler(GLFWwindow *window, double x, double y);
	void _windowMouseButtonHandler(GLFWwindow *window, int button, int action, int mods);
	void _windowMouseScrollHandler(GLFWwindow *window, double dx, double dy);

	class Window
	{
	protected:
		GLFWwindow *window;
		vector<Shader> shaders;

		int width, height;
		string title;

	public:
		Window() : window(NULL), width(INCD_WINDOW_DEFAULT_WIDTH), height(INCD_WINDOW_DEFAULT_HEIGHT), title(INCD_WINDOW_DEFAULT_TITLE) {}
		
		void setSize(int w, int h);
		int getWidth();
		int getHeight();
		int getX();
		int getY();
		void setTitle(string t);
		string getTitle();
		
		void hide();
		void show();
		void minimize();
		void restore();
		
		void loadContext();
		void init();
		bool isReady();
		void halt();
		void exec();

		void setPosition(int x, int y);
		int loadShader(Shader s);
		int loadShader(string v, string f);
		Shader &getShader(int n);
		void useShader(int n);

		virtual void keyHandler(Key &k, ModifierStatus &m, bool pressed);
		virtual void buttonHandler(int b, ModifierStatus &m, bool pressed);
		virtual void mouseHandler(double x, double y);
		virtual void scrollHandler(double x, double y);
		virtual void resizeHandler(int w, int h);
		virtual void loadHandler();
		virtual void renderHandler();
	};
}

#endif
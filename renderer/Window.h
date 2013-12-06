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
		vector<pair<string, Shader> > shaders;
		int currentShader;

		int width, height;
		string title;

	public:
		Window() : window(NULL), currentShader(-1), width(INCD_WINDOW_DEFAULT_WIDTH), height(INCD_WINDOW_DEFAULT_HEIGHT), title(INCD_WINDOW_DEFAULT_TITLE) {}
		
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
		void loadDefaultShaders();
		bool hasShader(int n);
		bool hasShader(string n);
		int loadShader(string n, Shader s);
		int loadShader(string n, string v, string f);
		int findShader(string n);
		Shader &getShader(int n = -1);
		Shader &getShader(string n);
		int getCurrentShader();
		void useShader(int n);
		void useShader(string n);

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
#ifndef __LIB_INCANDESCENCE_GL_UTIL_H
#define __LIB_INCANDESCENCE_GL_UTIL_H

#include "Util.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTFont.h>

#define INCD_GL_ERROR() incandescence::getGLError(__FILE__,__LINE__)

namespace incandescence
{
	using namespace std;

	extern int glMajorVersion, glMinorVersion;
	extern bool hasGlewBeenInitialized;
	extern bool hasContextBeenBound;
	
	void initGL(int maj = -1, int min = -1);
	void haltGL();
	void initGLEW();

	double getTime();
	void setTime(double t = 0);
	int getDPI();
	pair<int, int> getGLVersion();
	bool getGLError(string file = "", int linenum = -1);

	GLfloat pixelCoordXToGL(int x, int w);
	GLfloat pixelCoordYToGL(int y, int h);

	GLuint loadGLShaders(string vertexShaderPath, string fragmentShaderPath);
}

#endif
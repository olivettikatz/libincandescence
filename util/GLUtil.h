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

namespace incandescence
{
	using namespace std;

	extern int glMajorVersion, glMinorVersion;
	extern bool hasGlewBeenInitialized;
	extern bool hasContextBeenBound;
	extern bool hasFramebufferBeenCreated;
	
	void initGL(int maj = -1, int min = -1);
	void haltGL();
	void initGLEW();

	double getTime();
	void setTime(double t = 0);
	int getDPI();
	bool getGLError(string file = "", int linenum = -1);
	bool getGLFramebufferError(string file = "", int linenum = -1);

	GLfloat pixelCoordXToGL(int x, int w);
	GLfloat pixelCoordYToGL(int y, int h);

	GLuint loadGLShaders(string vertexShaderPath, string fragmentShaderPath);
}

#endif
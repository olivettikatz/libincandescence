#ifndef __LIB_INCANDESCENCE_FONT_RENDERER_H
#define __LIB_INCANDESCENCE_FONT_RENDERER_H

#include "../util/Util.h"
#include "../util/GLUtil.h"
#include "../renderer/Poly.h"
#include <FTGL/ftgl.h>
#include <FTGL/FTFont.h>

namespace incandescence
{
	using namespace std;
	using namespace FTGL;

	extern bool hasFTBeenInitialized;
	extern FT_Library ftlib;
	void initFontRendering();

	class Window;

	class FontRenderer
	{
	protected:
		string path;
		int dpi;
		int width, height;
		FTFont *font;
		FT_Face face;
		bool rastering;

		string symbolCoord, symbolTex, symbolColor;
		GLint attrCoord, uniformTex, uniformColor;
		GLuint vbo;

		void postLoad(GLuint pid = 0);
		void reportUnsupportedGLVersion(string n = "unknown FontRenderer::...");

	public:
		FontRenderer() : dpi(72), width(5), height(12), font(NULL), rastering(true), symbolCoord("coord"), symbolTex("tex"), symbolColor("textColor"), attrCoord(-1), uniformTex(-1), uniformColor(-1), vbo(0) {}
		FontRenderer(string p, int h, int w = -1) : path(p), dpi(72), width(w), height(h), font(NULL), rastering(true), symbolCoord("coord"), symbolTex("tex"), symbolColor("textColor"), attrCoord(-1), uniformTex(-1), uniformColor(-1), vbo(0) {if (width == -1) width = height/2;}
		void setShaderSymbolCoord(string s);
		void setShaderSymbolTex(string s);
		void setShaderSymbolColor(string s);
		GLint getUniformColor();
		void setDPI(int d);
		FTFont *getFont();
		void load2D(GLuint pid = 0);
		void load3D(GLuint pid = 0);
		void load3DOutline(int outline = -1, GLuint pid = 0);
		void load3DExtrude(int extrude = -1, GLuint pid = 0);
		void unload();
		bool good();
		void render(Window &w, string text, int x, int y);
		int getWidth(string text);
	};
}

#endif
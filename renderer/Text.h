#ifndef __LIB_INCANDESCENCE_TEXT_H
#define __LIB_INCANDESCENCE_TEXT_H

#include "Drawable.h"
#include "Color.h"
#include "../font/FontRenderer.h"

namespace incandescence
{
	using namespace std;

	class Text : public Drawable
	{
	public:
		int x, y;
		Color color;
		string text;
		FontRenderer *font;
		GLint uniformColor;

		Text() : x(0), y(0), font(NULL) {requireVersion(1, 4);}
		Text(string t, int _x, int _y, FontRenderer &f) : x(_x), y(_y), text(t), font(&f) {requireVersion(1, 4);}
		void loadHandler(Window &w);
		void renderHandler(Window &w);
	};
}

#endif
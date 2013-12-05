#ifndef __LIB_INCANDESCENCE_COLOR_H
#define __LIB_INCANDESCENCE_COLOR_H

#include "Drawable.h"

namespace incandescence
{
	using namespace std;

	class Color : public Drawable
	{
	public:
		unsigned char r, g, b, a;

		Color() : r(0), g(0), b(0), a(255) {}
		Color(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b), a(255) {}
		Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {}
		void load(Window &w);
		void render(Window &w);
		void applyToUniform(GLint uniform);
	};
}

#endif
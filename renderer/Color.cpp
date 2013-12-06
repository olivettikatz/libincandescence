#include "Color.h"

namespace incandescence
{
	void Color::renderHandler(Window &w)
	{
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			glColor4f(r/(float)255, g/(float)255, b/(float)255, a/(float)255);
		}
		else
		{
			INCD_REPORT_UNSUPPORTED_GL_VERSION();
		}
	}

	void Color::renderHandler(GLint so)
	{
		GLfloat tmp[4] = {
			r/(float)255,
			g/(float)255,
			b/(float)255,
			a/(float)255
		};
		glUniform4fv(so, 1, tmp);
	}
}

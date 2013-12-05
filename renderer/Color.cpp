#include "Color.h"

namespace incandescence
{
	void Color::load(Window &w)
	{
	}

	void Color::render(Window &w)
	{
		if (getGLVersion().first <= 2)
		{
			glColor4f(r/(float)255, g/(float)255, b/(float)255, a/(float)255);
			if (INCD_GL_ERROR())
				return ;
		}
		else
		{
			INCD_DRAWING_UNSUPPORTED_GL_ERROR("Color");
		}
	}

	void Color::applyToUniform(GLint uniform)
	{
		if (uniform == -1)
		{
			INCD_ERROR("cannot apply color to invalid uniform (-1).");
			return ;
		}

		GLfloat tmp[4] = {
			r/(float)255,
			g/(float)255,
			b/(float)255,
			a/(float)255
		};
		glUniform4fv(uniform, 1, tmp);
	}
}
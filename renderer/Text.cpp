#include "Text.h"

namespace incandescence
{
	void Text::loadHandler(Window &w)
	{
		if (INCD_GL_VERSION_MAJOR >= 3)
			uniformColor = w.getShader(INCD_SHADER_TEXT).getUniform("textColor");
	}

	void Text::renderHandler(Window &w)
	{
		if (INCD_GL_VERSION_MAJOR <= 2)
			color.render(w);
		else
			color.render(uniformColor);
		font->render(w, text, x, y);
	}
}

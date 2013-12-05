#include "Text.h"

namespace incandescence
{
	void Text::load(Window &w)
	{

	}

	void Text::render(Window &w)
	{
		color.applyToUniform(font->getUniformColor());
		font->render(w, text, x, y);
		if (INCD_GL_ERROR())
		{
			INCD_WARNING("errors occured during Text::'*::render'.");
			return ;
		}
	}
}
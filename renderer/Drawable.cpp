#include "Drawable.h"
#include "Window.h"

namespace incandescence
{
	void Drawable::requireVersion(int min, int max)
	{
		minVersion = min;
		maxVersion = max;
	}

	void Drawable::reportUnsupportedGLVersion(string file, int linenum)
	{
		INCD_ERROR("unsupported OpenGL version for this drawing instruction: " << INCD_GL_VERSION_MAJOR << "." << INCD_GL_VERSION_MINOR << " (" << file << ":" << linenum << ").");
	}

	bool Drawable::good()
	{
		return false;
	}

	void Drawable::load(Window &w)
	{
		if (minVersion == -1 || maxVersion == -1)
		{
			INCD_FATAL("Drawable/Drawable subclass does not call Drawable::requireVersion before method that requires version boundaries (minVersion == -1 || maxVersion == -1).");
		}
		else if (INCD_GL_VERSION_MAJOR < minVersion || INCD_GL_VERSION_MAJOR > maxVersion)
		{
			INCD_ERROR("unsupported OpenGL version for this drawing instruction (min: " << minVersion << ", max: " << maxVersion << ", current: " << INCD_GL_VERSION_MAJOR << ").");
		}
		else
		{
			loadHandler(w);
			if (INCD_GL_ERROR())
				INCD_WARNING("error(s) while running loadHandler<" << INCD_GL_VERSION_MAJOR << ">");
		}
	}

	void Drawable::loadHandler(Window &w)
	{
	}

	void Drawable::render(Window &w)
	{
		if (minVersion == -1 || maxVersion == -1)
			INCD_FATAL("Drawable/Drawable subclass does not call Drawable::requireVersion before method that requires version boundaries (minVersion == -1 || maxVersion == -1).");
		int shader = w.getCurrentShader();
		renderHandler(w);
		if (INCD_GL_ERROR())
			INCD_WARNING("error(s) while running renderHandler<" << INCD_GL_VERSION_MAJOR << ">");
		if (w.getCurrentShader() != shader)
			w.useShader(shader);
	}

	void Drawable::renderHandler(Window &w)
	{
	}

	void Drawable::render(GLint so)
	{
		if (minVersion == -1 || maxVersion == -1)
		{
			INCD_FATAL("Drawable/Drawable subclass does not call Drawable::requireVersion before method that requires version boundaries (minVersion == -1 || maxVersion == -1).");
		}
		else if (INCD_GL_VERSION_MAJOR < 3)
		{
			INCD_ERROR("unsupported OpenGL version for rendering to shader object (min: 3, max: 4, current: " << INCD_GL_VERSION_MAJOR << ").");
		}
		else if (so == -1)
		{
			INCD_ERROR("cannot render to invalid shader object (-1).");
		}
		else
		{
			renderHandler(so);
			if (INCD_GL_ERROR())
				INCD_WARNING("error(s) while running renderHandler for shader object");
		}
	}

	void Drawable::renderHandler(GLint so)
	{
	}
}

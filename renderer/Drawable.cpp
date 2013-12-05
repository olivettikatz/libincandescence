#include "Drawable.h"

namespace incandescence
{
	void Drawable::reportUnsupportedGLVersion(string n, string file, int linenum)
	{
		INCD_ERROR("unsupported OpenGL version for this drawing instruction (" << n << "): " << getGLVersion().first << "." << getGLVersion().second << " (" << file << ":" << linenum << ").");
	}

	void Drawable::load(Window &w)
	{
	}

	void Drawable::render(Window &w)
	{
	}
}

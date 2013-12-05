#ifndef __LIB_INCANDESCENCE_DRAWABLE_H
#define __LIB_INCANDESCENCE_DRAWABLE_H

#include "../util/Util.h"
#include "../util/GLUtil.h"

#define INCD_DRAWING_UNSUPPORTED_GL_ERROR(n) reportUnsupportedGLVersion(n, __FILE__, __LINE__)

namespace incandescence
{
	using namespace std;

	class Window;

	class Drawable
	{
	protected:
		void reportUnsupportedGLVersion(string n = "unknown Drawable::exec", string file = "", int linenum = -1);

	public:
		typedef enum
		{
			Points = GL_POINTS,
			SeparateLines = GL_LINES,
			ConnectedLines = GL_LINE_STRIP,
			StrokedPoly = GL_LINE_LOOP,
			SeparateTriangles = GL_TRIANGLES,
			ConnectedTriangles = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN,
			SeparateQuads = GL_QUADS,
			ConnectedQuads = GL_QUAD_STRIP,
			FilledPoly = GL_POLYGON
		} DrawingMode;

		virtual void load(Window &w);
		virtual void render(Window &w);
	};
}

#endif
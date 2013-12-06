#ifndef __LIB_INCANDESCENCE_DRAWABLE_H
#define __LIB_INCANDESCENCE_DRAWABLE_H

#include "../util/Util.h"
#include "../util/GLUtil.h"

#define INCD_REPORT_UNSUPPORTED_GL_VERSION() reportUnsupportedGLVersion(__FILE__,__LINE__)

namespace incandescence
{
	using namespace std;

	class Window;

	class Drawable
	{
	protected:
		int minVersion, maxVersion;
		void requireVersion(int min, int max);
		void reportUnsupportedGLVersion(string file, int linenum);

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

		Drawable() : minVersion(-1), maxVersion(-1) {}

		virtual bool good();
		void load(Window &w);
		virtual void loadHandler(Window &w);
		void render(Window &w);
		virtual void renderHandler(Window &w);
		void render(GLint so);
		virtual void renderHandler(GLint so);
	};
}

#endif
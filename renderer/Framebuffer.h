#ifndef __LIB_INCANDESCENCE_FRAMEBUFFER_H
#define __LIB_INCANDESCENCE_FRAMEBUFFER_H

#include "../util/GLUtil.h"
#include "Drawable.h"

/* THIS DOESN'T WORK YET */

namespace incandescence
{
	using namespace std;

	class Framebuffer : public Drawable
	{
	protected:
		GLuint fbo, fboTexture, rboDepth, vboFboVerts;
		GLint attribCoord, uniformTexture;

	public:
		Framebuffer() : fbo(0), fboTexture(0), rboDepth(0), attribCoord(-1), uniformTexture(-1) {requireVersion(3, 4);}
		void loadHandler(Window &w);
		void renderHandler(Window &w);
		void resize(int w, int h);
		void use(Window &w);
		void unuse();
	};
}

#endif
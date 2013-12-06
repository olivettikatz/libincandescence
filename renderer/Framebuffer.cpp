#include "Framebuffer.h"
#include "Window.h"

namespace incandescence
{
	void Framebuffer::loadHandler(Window &w)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &fboTexture);
		glBindTexture(GL_TEXTURE_2D, fboTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w.getWidth(), w.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors while creating framebuffer texture object.");

		glGenFramebuffersEXT(1, &fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, fboTexture, 0);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors while creating framebuffer object.");

		glGenRenderbuffersEXT(1, &rboDepth);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboDepth);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, w.getWidth(), w.getHeight());

		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboDepth);
		hasFramebufferBeenCreated = true;

		//glBindRenderbuffer(GL_RENDERBUFFER, 0);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors in framebuffer configuration.");

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//if (INCD_GL_ERROR())
		//	INCD_WARNING("errors while creating framebuffer object.");

		attribCoord = w.getShader(INCD_SHADER_POST_PROCESSING).getAttribute("coord");
		uniformTexture = w.getShader(INCD_SHADER_POST_PROCESSING).getUniform("tex");

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Framebuffer::renderHandler(Window &w)
	{
		w.useShader(INCD_SHADER_POST_PROCESSING);

		GLfloat fboVerts[] = {
			-1, -1,
			1, -1,
			-1, 1,
			1, 1
		};

		glGenBuffers(1, &vboFboVerts);
		glBindBuffer(GL_ARRAY_BUFFER, vboFboVerts);
		glBufferData(GL_ARRAY_BUFFER, sizeof(fboVerts), fboVerts, GL_DYNAMIC_DRAW);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, fboTexture);
		glUniform1i(uniformTexture, 0);
		glEnableVertexAttribArray(attribCoord);

		glBindBuffer(GL_ARRAY_BUFFER, vboFboVerts);
		glVertexAttribPointer(attribCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableVertexAttribArray(attribCoord);

		if (INCD_GL_ERROR())
			INCD_WARNING("errors while rendering framebuffer object.");
	}

	void Framebuffer::resize(int w, int h)
	{
		glBindTexture(GL_TEXTURE_2D, fboTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors while resizing framebuffer texture object.");

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboDepth);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, w, h);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors while resizing framebuffer depth object.");
	}

	void Framebuffer::use(Window &w)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors while binding framebuffer object.");
	}

	void Framebuffer::unuse()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		if (INCD_GL_ERROR())
			INCD_WARNING("errors while unbinding framebuffer object.");
	}
}

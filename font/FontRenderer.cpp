#include "FontRenderer.h"
#include "../renderer/Window.h"

namespace incandescence
{
	bool hasFTBeenInitialized = false;
	FT_Library ftlib;

	void initFontRendering()
	{
		if (hasFTBeenInitialized == false)
		{
			if (FT_Init_FreeType(&ftlib))
			{
				INCD_ERROR("could not initialize freetype library.");
			}

			hasFTBeenInitialized = true;
		}
	}

	void FontRenderer::postLoad(Window &w)
	{
		if (INCD_GL_ERROR())
		{
			INCD_WARNING("errors during 'FontRenderer::load*' (before 'postLoad').");
		}

		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			if (!font)
			{
				INCD_ERROR("could not load font: " << path);
				return ;
			}

			if (dpi != -1)
			{
				if (!font->FaceSize(height, dpi))
				{
					INCD_ERROR("could not set font height: " << path << " (" << height << ").");
					delete font;
					return ;
				}
			}
			else
			{
				if (!font->FaceSize(height))
				{
					INCD_ERROR("could not set font height: " << path << " (" << height << ").");
					delete font;
					return ;
				}
			}
		}
		else
		{
			uniformTex = w.getShader(INCD_SHADER_TEXT).getUniform("tex");
			attrCoord = w.getShader(INCD_SHADER_TEXT).getAttribute("coord");

			glGenBuffers(1, &vbo);
			if (INCD_GL_ERROR())
				INCD_WARNING("errors when creating vertex buffer object.");
		}
	}

	void FontRenderer::setDPI(int d)
	{
		dpi = d;
	}

	FTFont *FontRenderer::getFont()
	{
		return font;
	}

	void FontRenderer::load2D(Window &w)
	{
		rastering = true;
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			font = new FTPixmapFont(path.c_str());
		}
		else
		{
			INCD_GL_VERSION_ERROR();
		}
		postLoad(w);
	}

	void FontRenderer::load3D(Window &w)
	{
		rastering = false;
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			font = new FTPolygonFont(path.c_str());
		}
		else if (INCD_GL_VERSION_MAJOR >= 3)
		{
			if (FT_New_Face(ftlib, path.c_str(), 0, &face))
			{
				INCD_ERROR("could not load font '" << path << "'.");
			}

			FT_Set_Pixel_Sizes(face, 0, height);
		}
		postLoad(w);
	}

	void FontRenderer::load3DOutline(Window &w, int outline)
	{
		rastering = false;
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			font = new FTOutlineFont(path.c_str());
		}
		else
		{
			INCD_GL_VERSION_ERROR();
		}
		postLoad(w);
		if (INCD_GL_VERSION_MAJOR <= 2 && font)
			font->Outset((float)outline);
	}

	void FontRenderer::load3DExtrude(Window &w, int extrude)
	{
		rastering = false;
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			font = new FTExtrudeFont(path.c_str());
		}
		else
		{
			INCD_GL_VERSION_ERROR();
		}
		postLoad(w);
		if (INCD_GL_VERSION_MAJOR <= 2 && font)
			font->Depth((float)extrude);
	}

	void FontRenderer::unload()
	{
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			if (font)
				delete font;
		}
	}

	bool FontRenderer::good()
	{
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			return (font != NULL);
		}
		else
		{
			return (face != NULL);
		}
	}

	void FontRenderer::render(Window &w, string text, int x, int y)
	{
		if (good())
		{
			if (INCD_GL_VERSION_MAJOR <= 2)
			{
				if (rastering)
					glRasterPos2f(x, y);
				else
					glTranslatef(x, y, 0.0f);
				font->Render(text.c_str());
			}
			else if (INCD_GL_VERSION_MAJOR >= 3)
			{
				FT_GlyphSlot gs = face->glyph;
				GLuint tex;

				glActiveTexture(GL_TEXTURE0);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while selecting texture for font rendering.");
					return ;
				}
				glGenTextures(1, &tex);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while creating font rendering texture.");
					return ;
				}
				glBindTexture(GL_TEXTURE_2D, tex);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while binding font rendering texture.");
					return ;
				}
				glUniform1i(uniformTex, 0);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while binding texture uniform.");
					return ;
				}

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while configuring data alignment.");
					return ;
				}

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while configuring font rendering texture.");
					return ;
				}

				glEnableVertexAttribArray(attrCoord);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glVertexAttribPointer(attrCoord, 4, GL_FLOAT, GL_FALSE, 0, 0);
				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors while binding data to vertex buffer object.");
					return ;
				}

				for (string::iterator i = text.begin(); i != text.end(); i++)
				{
					if (FT_Load_Char(face, *i, FT_LOAD_RENDER))
					{
						INCD_ERROR("failed to load character '" << *i << "' of string '" << text << "'");
						continue;
					}

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, gs->bitmap.width, gs->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, gs->bitmap.buffer);
					if (INCD_GL_ERROR())
					{
						INCD_WARNING("errors while binding 2D image to texture for font rendering.");
						break;
					}

					float x2 = pixelCoordXToGL(x, w.getWidth()) + gs->bitmap_left * 2.0/w.getWidth();
					float y2 = -pixelCoordYToGL(y, w.getHeight()) - gs->bitmap_top * 2.0/w.getHeight();
					float w2 = gs->bitmap.width * 2.0/w.getWidth();
					float h2 = gs->bitmap.rows * 2.0/w.getHeight();

					struct
					{
						GLfloat x, y, s, t;
					} box[4] = {
						{x2, -y2, 0, 0},
						{x2 + w2, -y2, 1, 0},
						{x2, -y2 - h2, 0, 1},
						{x2 + w2, -y2 - h2, 1, 1}
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

					x += (gs->advance.x >> 6);
					y += (gs->advance.y >> 6);
				}

				if (INCD_GL_ERROR())
				{
					INCD_WARNING("errors during 'FontRenderer::render' (did you call 'initFontRendering()'?).");
					return ;
				}

				glDisableVertexAttribArray(attrCoord);
				glDeleteTextures(1, &tex);
			}
		}
	}

	int FontRenderer::getWidth(string text)
	{
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			if (good())
				return font->Advance(text.c_str());
			else
				return -1;
		}
		else if (INCD_GL_VERSION_MAJOR >= 3)
		{
			return -1;
		}

		return -1;
	}
}
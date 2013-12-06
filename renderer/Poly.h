#ifndef __LIB_INCANDESCENCE_POLY_H
#define __LIB_INCANDESCENCE_POLY_H

#include "Drawable.h"
#include "Color.h"
#include "Window.h"

namespace incandescence
{
	using namespace std;

	template<Drawable::DrawingMode M> class Poly : public Drawable
	{
	public:
		Color color;
		vector<GLfloat> vbd;
		GLuint vao, vbo, cbo;

		Poly<M>() {requireVersion(1, 4);}
		Poly<M> &operator << (int v);
		Poly<M> &operator << (GLfloat v);
		void vertex(int x, int y);
		void loadHandler(Window &w);
		void renderHandler(Window &w);
	};

	template<Drawable::DrawingMode M> Poly<M> &Poly<M>::operator << (int v)
	{
		vbd.push_back((GLfloat)v);
	}

	template<Drawable::DrawingMode M> Poly<M> &Poly<M>::operator << (GLfloat v)
	{
		vbd.push_back(v);
	}

	template<Drawable::DrawingMode M> void Poly<M>::vertex(int x, int y)
	{
		vbd.push_back(x);
		vbd.push_back(y);
		vbd.push_back(0.0f);
	}

	template<Drawable::DrawingMode M> void Poly<M>::loadHandler(Window &w)
	{
		if (vbd.size()%3 != 0)
		{
			INCD_ERROR("Poly does not have vertecies in triplets (size % 3 != 0)");
			return ;
		}

		if (INCD_GL_VERSION_MAJOR >= 3)
		{
			vector<GLfloat> cbd;
			vector<GLfloat> vbdNormal;
			for (int i = 0; i < vbd.size(); i += 3)
			{
				cbd.push_back(color.r/(float)255);
				cbd.push_back(color.g/(float)255);
				cbd.push_back(color.b/(float)255);

				GLfloat x = pixelCoordXToGL(vbd[i], w.getWidth());
				GLfloat y = pixelCoordYToGL(vbd[i+1], w.getHeight());
				vbdNormal.push_back(x);
				vbdNormal.push_back(y);
				vbdNormal.push_back(0.0f);
			}

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vbdNormal.size(), vbdNormal.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &cbo);
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*cbd.size(), cbd.data(), GL_STATIC_DRAW);
		}
	}

	template<Drawable::DrawingMode M> void Poly<M>::renderHandler(Window &w)
	{
		if (INCD_GL_VERSION_MAJOR <= 2)
		{
			glBegin(M);

			color.render(w);

			for (int i = 0; i < vbd.size(); i += 3)
			{
				glVertex3f(vbd[i], vbd[i+1], vbd[i+2]);
			}

			glEnd();
		}
		else
		{
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			glDrawArrays(M, 0, vbd.size()/3);
			glDisableVertexAttribArray(0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			glDisableVertexAttribArray(0);
		}
	}
}

#endif
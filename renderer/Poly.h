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

		Poly<M>() {}
		Poly<M> &operator << (int v);
		Poly<M> &operator << (GLfloat v);
		void vertex(int x, int y);
		void load(Window &w);
		void render(Window &w);
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

	template<Drawable::DrawingMode M> void Poly<M>::load(Window &w)
	{
		if (vbd.size()%3 != 0)
		{
			INCD_ERROR("Poly does not have vertecies in triplets (size % 3 != 0)");
			return ;
		}

		if (getGLVersion().first >= 3)
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
			if (INCD_GL_ERROR())
						return ;
			glBindVertexArray(vao);
			if (INCD_GL_ERROR())
						return ;

			glGenBuffers(1, &vbo);
			if (INCD_GL_ERROR())
						return ;
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			if (INCD_GL_ERROR())
						return ;
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vbdNormal.size(), vbdNormal.data(), GL_STATIC_DRAW);
			if (INCD_GL_ERROR())
						return ;

			glGenBuffers(1, &cbo);
			if (INCD_GL_ERROR())
						return ;
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			if (INCD_GL_ERROR())
						return ;
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*cbd.size(), cbd.data(), GL_STATIC_DRAW);
			if (INCD_GL_ERROR())
						return ;
		}

		if (INCD_GL_ERROR())
			INCD_WARNING("errors occured during loading of 'Poly<M>'.");
	}

	template<Drawable::DrawingMode M> void Poly<M>::render(Window &w)
	{
		if (getGLVersion().first <= 2)
		{
			glBegin(M);
			if (INCD_GL_ERROR())
				return ;

			color.render(w);

			for (int i = 0; i < vbd.size(); i += 3)
			{
				glVertex3f(vbd[i], vbd[i+1], vbd[i+2]);
				if (INCD_GL_ERROR())
				return ;
			}

			glEnd();
			if (INCD_GL_ERROR())
				return ;
		}
		else if (getGLVersion().first >= 3)
		{
			glEnableVertexAttribArray(0);
			if (INCD_GL_ERROR())
					return ;
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			if (INCD_GL_ERROR())
					return ;
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			if (INCD_GL_ERROR())
					return ;
			glDrawArrays(M, 0, vbd.size()/3);
			if (INCD_GL_ERROR())
					return ;
			glDisableVertexAttribArray(0);
			if (INCD_GL_ERROR())
					return ;

			glEnableVertexAttribArray(1);
			if (INCD_GL_ERROR())
					return ;
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			if (INCD_GL_ERROR())
					return ;
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			if (INCD_GL_ERROR())
					return ;
			glDisableVertexAttribArray(0);
			if (INCD_GL_ERROR())
					return ;
		}
		else
		{
			INCD_DRAWING_UNSUPPORTED_GL_ERROR("Poly");
		}

		if (INCD_GL_ERROR())
		{
			INCD_WARNING("errors occured during rendering of 'Poly<M>'");
		}
	}
}

#endif
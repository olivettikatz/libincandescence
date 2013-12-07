/* Copyright 2013 Oliver Katz
 *
 * This file is part of LibIncandescence.
 *
 * LibIncandescence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LibIncandescene is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibIncandescence.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file Poly.h
 *  \brief Subclass of Drawable for drawing polygons. */

#ifndef __LIB_INCANDESCENCE_POLY_H
#define __LIB_INCANDESCENCE_POLY_H

#include "Drawable.h"
#include "Color.h"
#include "Window.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! \brief Subclass of Drawable for drawing polygons.
	 *  Takes template argument of polygon drawing mode (see Drawable.h). */
	template<Drawable::DrawingMode M> class Poly : public Drawable
	{
	public:
		/*! Color to draw in. */
		Color color;

		/*! Vertex buffer data (where polygon data is stored for OpenGL). */
		vector<GLfloat> vbd;

		/*! Vertex Array Object, Vertex Buffer Object, and Buffer Object. */
		GLuint vao, vbo, cbo;

		/*! Constructor. */
		Poly<M>() {requireVersion(1, 4);}

		/*! Append pixel coordinate. 
		 *  \warning OpenGL 1-2 only. */
		Poly<M> &operator << (int v);

		/*! Append OpenGL coordinate. */
		Poly<M> &operator << (GLfloat v);

		/*! Append pixel coordinate vertex. */
		void vertex(int x, int y);

		/*! Load polygon data. */
		void loadHandler(Window &w);

		/*! Renders polygon. */
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
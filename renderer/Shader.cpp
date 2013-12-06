#include "Shader.h"

namespace incandescence
{
	GLuint Shader::getPid()
	{
		return pid;
	}

	bool Shader::good()
	{
		return (pid != 0);
	}

	void Shader::useVertexScript(string v)
	{
		vertPath = v;
	}

	void Shader::useFragmentScript(string f)
	{
		fragPath = f;
	}

	void Shader::useScripts(string v, string f)
	{
		vertPath = v;
		fragPath = f;
	}

	void Shader::load()
	{
		pid = loadGLShaders(vertPath, fragPath);
	}

	void Shader::unload()
	{
		pid = 0; // this is not resource efficient, but hey
	}

	void Shader::use()
	{
		if (pid == 0)
		{
			INCD_ERROR("invalid GL program ID (0).");
			return ;
		}

		glUseProgram(pid);
		if (INCD_GL_ERROR())
			return ;
	}

	GLint Shader::getAttribute(string s)
	{
		GLint tmp = glGetAttribLocation(pid, s.c_str());
		if (tmp == -1)
		{
			INCD_FATAL("could not find GLSL attribute '" << s << "'");
			return -1;
		}
		return tmp;
	}

	GLint Shader::getUniform(string s)
	{
		GLint tmp = glGetUniformLocation(pid, s.c_str());
		if (tmp == -1)
		{
			INCD_FATAL("could not find GLSL uniform '" << s << "'");
			return -1;
		}
		return tmp;
	}
}
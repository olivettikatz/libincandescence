#include "Shader.h"

namespace incandescence
{
	GLuint Shader::getPid()
	{
		return pid;
	}

	bool Shader::good()
	{
		if (vertPath.empty())
			return false;

		if (fragPath.empty())
			return false;

		if (pid == 0)
			return false;

		return true;
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
}
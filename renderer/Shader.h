#ifndef __LIB_INCANDESCENCE_SHADER_H
#define __LIB_INCANDESCENCE_SHADER_H

#include "../util/GLUtil.h"

namespace incandescence
{
	using namespace std;

	class Shader
	{
	protected:
		string vertPath, fragPath;
		GLuint pid;

	public:
		Shader(string v = "", string f = "") : vertPath(v), fragPath(f), pid(0) {}
		GLuint getPid();
		bool good();
		void useVertexScript(string v);
		void useFragmentScript(string f);
		void useScripts(string v, string f);
		void load();
		void unload();
		void use();
	};
}

#endif
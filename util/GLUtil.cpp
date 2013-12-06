#include "GLUtil.h"

namespace incandescence
{
	int glMajorVersion = 0, glMinorVersion = 0;
	bool hasGlewBeenInitialized = false;
	bool hasContextBeenBound = false;
	bool hasFramebufferBeenCreated = false;

	void initGL(int maj, int min)
	{
		if (!glfwInit())
		{
			INCD_FATAL("could not initialize OpenGL (GLFW).");
		}

		if (maj != -1 && min != -1)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
	}

	void haltGL()
	{
		glfwTerminate();
	}

	void initGLEW()
	{
		if (hasGlewBeenInitialized == false)
		{
			if (INCD_GL_ERROR())
				return ;
			glewExperimental = GL_TRUE;
			if (INCD_GL_ERROR())
				return ;
			GLenum e = glewInit();
			if (e != GLEW_OK)
			{
				INCD_FATAL("error while initializing GLEW: " << glewGetErrorString(e));
				return ;
			}
			if (INCD_GL_ERROR())
				return ;
			hasGlewBeenInitialized = true;
		}
	}

	double getTime()
	{
		return glfwGetTime();
	}

	void setTime(double t)
	{
		glfwSetTime(t);
	}

	int getDPI()
	{
		int w, h;
		GLFWmonitor *primary = glfwGetPrimaryMonitor();
		glfwGetMonitorPhysicalSize(primary, &w, &h);
		const GLFWvidmode *mode = glfwGetVideoMode(primary);
		return (int)(mode->width / (w / 25.4));
	}

	bool getGLError(string file, int linenum)
	{
		if (hasContextBeenBound == false)
			return false;

		GLenum e = glGetError();
		if (e == GL_NO_ERROR)
		{
			return false;
		}
		else if (e == GL_INVALID_ENUM)
		{
			INCD_ERROR("OpenGL error (GL_INVALID_ENUM): unacceptable enumerated argument (" << file << ":" << linenum << ").");
		}
		else if (e == GL_INVALID_VALUE)
		{
			INCD_ERROR("OpenGl error (GL_INVALID_VALUE): numeric argument out of range (" << file << ":" << linenum << ").");
		}
		else if (e == GL_INVALID_OPERATION)
		{
			INCD_ERROR("OpenGL error (GL_INVALID_OPERATION): specified operation is not allowed in current state (" << file << ":" << linenum << ").");
		}
		else if (e == GL_OUT_OF_MEMORY)
		{
			INCD_ERROR("OpenGL error (GL_OUT_OF_MEMORY): not enough memory to execute command (" << file << ":" << linenum << ").");
		}
		else if (e == GL_STACK_UNDERFLOW)
		{
			INCD_ERROR("OpenGL error (GL_STACK_UNFLOW): attempted operation would cause stack underflow (" << file << ":" << linenum << ").");
		}
		else if (e == GL_STACK_OVERFLOW)
		{
			INCD_ERROR("OpenGL error (GL_STACK_UNFLOW): attempted operation would cause stack overflow (" << file << ":" << linenum << ").");
		}
		else
		{
			INCD_ERROR("OpenGL error (?): unknown error code (" << file << ":" << linenum << ").");
		}

		return true;
	}

	bool getGLFramebufferError(string file, int linenum)
	{
		if (hasContextBeenBound == false || hasFramebufferBeenCreated == false)
			return false;

		GLuint s = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (s == GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT): unable to bind attachment for framebuffer object (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT): mismatched dimensions of buffers and framebuffer (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT): mismatched or unsupported formats of buffers and framebuffer (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER): incomplete or undefined draw buffer (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER): incomplete or undefined read buffer (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE): mismatched number of multisample samples (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS): mismatched layered and unlayered attachments (" << file << ":" << linenum << ").");
		}
		else if (s == GL_FRAMEBUFFER_UNSUPPORTED)
		{
			INCD_ERROR("OpenGL framebuffer error (GL_FRAMEBUFFER_UNSUPPORTED): unknown error while creating frame buffer (" << file << ":" << linenum << ").");
		}
		else
		{
			INCD_ERROR("OpenGL framebuffer error (?): unknown error while creating frame buffer (" << file << ":" << linenum << ").");
		}

		return true;
	}

	GLfloat pixelCoordXToGL(int x, int w)
	{
		return (x-w/2)/((float)w/2);
	}

	GLfloat pixelCoordYToGL(int y, int h)
	{
		return ((h-y)-h/2)/((float)h/2);
	}

	// CREDIT GOES TO NEHE PRODUCTIONS FOR THIS METHOD
	GLuint loadGLShaders(string vertexShaderPath, string fragmentShaderPath)
	{
		if (hasContextBeenBound == false)
		{
			INCD_ERROR("cannot load GLSL shaders until GL context has been bound (Window::loadContext).");
			return 0;
		}

	    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	    if (INCD_GL_ERROR())
			return 0;
	    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	    if (INCD_GL_ERROR())
			return 0;
	    
	    std::string VertexShaderCode = loadFile(vertexShaderPath);
	    std::string FragmentShaderCode = loadFile(fragmentShaderPath);
	 
	    GLint Result = GL_FALSE;
	    int InfoLogLength;
	 
	    char const * VertexSourcePointer = VertexShaderCode.c_str();
	    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	    glCompileShader(VertexShaderID);
	    
	    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	    if (InfoLogLength > 0)
	    {
	    	cout << &VertexShaderErrorMessage[0] << "\n";
	    	INCD_FATAL("error(s) while compiling vertex shader (" << vertexShaderPath << ").");
	    }
	 
	    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	    glCompileShader(FragmentShaderID);
	    
	    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	    if (InfoLogLength > 0)
	    {
	    	cout << &FragmentShaderErrorMessage[0] << "\n";
	    	INCD_FATAL("error(s) while compiling fragment shader (" << fragmentShaderPath << ").");
	    }
	 
	    GLuint ProgramID = glCreateProgram();
	    glAttachShader(ProgramID, VertexShaderID);
	    glAttachShader(ProgramID, FragmentShaderID);
	    glLinkProgram(ProgramID);
	    
	    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	    if (InfoLogLength > 0)
	    {
	    	cout << &ProgramErrorMessage[0] << "\n";
	    	INCD_FATAL("error(s) while linking shader program (" << vertexShaderPath << " with " << fragmentShaderPath << ").");
	    }
	 
	    glDeleteShader(VertexShaderID);
	    glDeleteShader(FragmentShaderID);
	    
	    return ProgramID;
	}
}
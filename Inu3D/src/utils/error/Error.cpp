#include "Error.h"

#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << GLGetErrorString(error) 
			 << " in file " << file << " (" << line << ")" << std::endl;
		return false;
	}
	return true;
}

const char* GLGetErrorString(GLenum error)
{
	switch (error)
	{
	case GL_INVALID_ENUM:                  return "Invalid Enum"; break;
	case GL_INVALID_VALUE:                 return "Invalid Value"; break;
	case GL_INVALID_OPERATION:             return "Invalid Operation"; break;
	case GL_STACK_OVERFLOW:                return "Stack Overflow"; break;
	case GL_STACK_UNDERFLOW:               return "Stack Underflow"; break;
	case GL_OUT_OF_MEMORY:                 return "Out of Memory"; break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid Framebuffer Operation"; break;
	default:							   return "Unknown Error";
	}
}

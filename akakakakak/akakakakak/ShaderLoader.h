#pragma once
#include <string>
#include <fstream>
#include "include/GL/glew.h"
#include "include/GL/glut.h"

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/freeglut.lib")

namespace Core {
	class Shader_Loader
	{
	private:
		std::string ReadShader(char* filename);
		GLuint CreateShader(GLenum shaderType, std::string source, const char* shaderName);
	public:
		Shader_Loader(void);
		~Shader_Loader(void);
		GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);
	};
}
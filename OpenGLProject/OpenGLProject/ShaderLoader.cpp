#include "pch.h"
#include "ShaderLoader.h"

using namespace Core;

static GLuint programId = 0; // program ID
static GLuint vsId = 0; // vertex shader ID
static GLuint fsId = 0; // fragment shader ID
const char* vsFile = "VertexShader.glsl"; // vertex shader file
const char* fsFile = "FragmentShader.glsl"; // fragment shader file

char* Core::textFromFile(const char* filePathName, int& textLength)
{
	char* text = (char*)NULL;

	// Open the file and move the current position to the end position of the file.
	std::ifstream file(filePathName, std::ios::in | std::ios::ate);

	textLength = file.tellg(); // the current position
	text = new char[textLength + 1]; // memory allocation for storing text
	file.seekg(0, std::ios::beg); // move to the start position of the file
	file.read(text, textLength); // read data
	file.close(); // close the file

	if (text) { text[textLength] = '\0'; }

	return text;
}

void Core::InitShaders()
{
	///////////////////
	// vertex shader //
	{
		// 1) Create a shader object.
		vsId = glCreateShader(GL_VERTEX_SHADER);

		// 2) Load a shader source code from a file.
		int vsSrcLen = 0; // the length of the shader source code
		const char* vsSrc = textFromFile(vsFile, vsSrcLen); // shader source code text

		// 3) Specify the shader source code.
		glShaderSource(vsId, 1, &vsSrc, &vsSrcLen);

		// 4) Compile the shader.
		glCompileShader(vsId);
	}

	/////////////////////
	// fragment shader //
	{
		// 1) Create a shader object.
		fsId = glCreateShader(GL_FRAGMENT_SHADER);

		// 2) Load a shader source code from a file.
		int fsSrcLen = 0; // the length of the shader source code
		const char* fsSrc = textFromFile(fsFile, fsSrcLen); // shader source code text

		// 3) Specify the shader source code.
		glShaderSource(fsId, 1, &fsSrc, &fsSrcLen);

		// 4) Compile the shader.
		glCompileShader(fsId);
	}

	/////////////
	// program //

	// Create a program object to attach the shaders into.
	programId = glCreateProgram();

	// Attach the compiled shaders to the program object.
	glAttachShader(programId, vsId);
	glAttachShader(programId, fsId);

	// Link the program object to the application.
	glLinkProgram(programId);

	// Disable the programmable processors so that the fixed functionality will be used.
	glUseProgram(programId);
}
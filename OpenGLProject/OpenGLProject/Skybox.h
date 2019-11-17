#pragma once
#include "Shader.h"
#include "DebugOutput.h"

class Skybox
{
private:
	GLuint id = -1; // program id입니다
	GLuint vaoId = -1; // VAO의 id입니다
	GLuint vboId = -1; // VBO의 id입니다
public:
	Skybox(void);
	Skybox(const Shader& shader, const std::string& fdir);
public:
	void Draw(void);
private:
	void CreateVAO_VBO(void);
};
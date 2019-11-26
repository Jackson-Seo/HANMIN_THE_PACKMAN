#pragma once
#include "Shader.h"
#include "DebugOutput.h"

class Skybox
{
private:
	GLuint id = -1; // program id�Դϴ�
	GLuint vaoId = -1; // VAO�� id�Դϴ�
	GLuint vboId = -1; // VBO�� id�Դϴ�
public:
	Skybox(void);
	Skybox(const Shader& shader, const std::string& fdir);
public:
	void Draw(void);
private:
	void CreateVAO_VBO(void);
};
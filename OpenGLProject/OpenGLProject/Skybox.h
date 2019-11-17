#pragma once
#include "Shader.h"
#include "Output.h"

class Skybox
{
private:
	GLuint id = -1;
	GLuint vaoId;
	GLuint vboId;
public:
	Skybox(void);
	Skybox(const Shader& shader, const std::string& fdir);
public:
	void Draw(void);
private:
	void CreateVAO_VBO(void);
};
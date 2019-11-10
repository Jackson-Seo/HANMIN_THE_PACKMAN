#pragma once
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
private:
	// program ID
	GLuint ID;
public:
	// �����ڴ� shader�� �а� �����մϴ�.
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	// shader�� Ȱ��ȭ�ϰ� ����մϴ�.
	void use();
	// Uniform ��ƿ��Ƽ �Լ���
	void setMatrix(glm::mat4& matrix, const std::string& str) const;
	GLuint getID(void);
};
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
	void setMatrix(const glm::mat4& matrix, const std::string& str) const;
	void setVec3(const glm::vec3& vec, const std::string& str) const;
	GLuint getID(void);
};
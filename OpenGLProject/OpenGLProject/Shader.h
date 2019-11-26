#pragma once
#include <fstream>
#include <sstream>
#include "DebugOutput.h"

class Shader
{
private:
	// program ID
	GLuint ID;
public:
	// �����ڴ� shader�� �а� �����մϴ�.
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	// shader�� Ȱ��ȭ�ϰ� ����մϴ� shader�� ����Ϸ��� �ݵ�� ȣ���ؾ� �մϴ�
	void use();
	// Uniform ��ƿ��Ƽ �Լ��� Shader�� Uniform ������ ���� �����Ҷ� ����մϴ�
	void setfloat(const GLfloat& value, const std::string& str) const;
	void setVec3(const glm::vec3& vec, const std::string& str) const;
	void setVec4(const glm::vec4& vec, const std::string& str) const;
	void setMatirx3(const glm::mat4& matrix, const std::string& str) const;
	void setMatrix4(const glm::mat4& matrix, const std::string& str) const;
	void setUniform1(const GLuint& i, const std::string& str) const;
	// Shader ��ü�� Program ID�� ������ ����մϴ�
	GLuint getID(void) const;
};
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
	void setVec3(const glm::vec3& const vec, const std::string& str) const;
	void setMatirx3(const glm::mat4& const matrix, const std::string& str) const;
	void setMatrix4(const glm::mat4& const matrix, const std::string& str) const;
	void setUniform1(const GLuint& i, const  std::string& str) const;
	void setUniform4f();
	GLuint getID(void) const;
};
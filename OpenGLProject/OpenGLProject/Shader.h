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
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// shader�� Ȱ��ȭ�ϰ� ����մϴ�.
	void use();
	// Uniform ��ƿ��Ƽ �Լ���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	GLuint getID(void);
};
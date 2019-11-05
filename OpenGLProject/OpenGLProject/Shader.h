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
	// 생성자는 shader를 읽고 생성합니다.
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// shader를 활성화하고 사용합니다.
	void use();
	// Uniform 유틸리티 함수들
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	GLuint getID(void);
};
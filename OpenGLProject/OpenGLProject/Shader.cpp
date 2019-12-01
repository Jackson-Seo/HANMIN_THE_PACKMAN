#include "pch.h"
#include "Shader.h"

// Shader ��ü �������Դϴ� glsl������ ����� ��θ� �Է¹޾� �������Ͽ� Shader�� ����մϴ�
Shader::Shader() {}
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. ���� ��θ� ���� vertex/fragment shader �ҽ� �ڵ带 �˻��մϴ�.
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ifstream ��ü���� ���ܸ� ���� �� �ֵ��� �մϴ�.
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// ���� ����
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// stream�� ������ ���� ������ �б�
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// ���� �ڵ鷯 �ݱ�
		vShaderFile.close();
		fShaderFile.close();
		// stream�� string���� ��ȯ
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		// std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		trace1("\nERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	{
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// ������ �߻��Ѵٸ� ������ ������ ���
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			TRACE0("\nVertex Shader �ҷ����� �� ���� �߻�\n");
			// std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
	}
	// Fragment shader�� ��������
	{
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// ������ �߻��Ѵٸ� ������ ������ ���
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			TRACE0("\nFragment Shader �ҷ����� �� ���� �߻�\n");
			// std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
	}

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// ������ �߻��Ѵٸ� ��ŷ ������ ���
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		// std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// program ���ο��� shader���� ��ũ �Ϸ�Ǿ��ٸ� ���� �ʿ� �����Ƿ� shader���� ����
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(ID); } // shader�� Ȱ��ȭ�ϰ� ����մϴ� shader�� ����Ϸ��� �ݵ�� ȣ���ؾ� �մϴ�
// Uniform ��ƿ��Ƽ �Լ��� Shader�� Uniform ������ ���� �����Ҷ� ����մϴ�
void Shader::setfloat(const GLfloat& value, const std::string& str) const { glUniform1f(glGetUniformLocation(ID, str.c_str()), value); }
void Shader::setfloatv(const GLfloat* value, const int& size,const std::string& str) const { glUniform1fv(glGetUniformLocation(ID, str.c_str()), size, value); }
void Shader::setVec3(const glm::vec3& vec, const std::string& str) const { glUniform3fv(glGetUniformLocation(ID, str.c_str()), 1, glm::value_ptr(vec)); }
void Shader::setVec3v(const glm::vec3& vec, const int& size, const std::string& str) const { glUniform3fv(glGetUniformLocation(ID, str.c_str()), size, glm::value_ptr(vec)); }
void Shader::setVec4(const glm::vec4& vec, const std::string& str) const { glUniform4fv(glGetUniformLocation(ID, str.c_str()), 1, glm::value_ptr(vec)); }
void Shader::setMatirx3(const glm::mat4& matrix, const std::string& str) const { glUniformMatrix3fv(glGetUniformLocation(ID, str.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); }
void Shader::setMatrix4(const glm::mat4& matrix, const std::string& str) const { glUniformMatrix4fv(glGetUniformLocation(ID, str.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); }
void Shader::setUniform1i(const GLuint& i, const std::string& str) const { glUniform1i(glGetUniformLocation(ID, str.c_str()), i); }
void Shader::setUniform1f(const GLfloat& f, const std::string& str) const { glUniform1f(glGetUniformLocation(ID, str.c_str()), f); }
// Shader ��ü�� Program ID�� ������ ����մϴ�
GLuint Shader::getID(void) const { return ID; }
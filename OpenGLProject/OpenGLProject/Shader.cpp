#include "pch.h"
#include "Shader.h"

// Shader 객체 생성자입니다 glsl파일이 저장된 경로를 입력받아 컴파일하여 Shader로 사용합니다
Shader::Shader() {}
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. 파일 경로를 통해 vertex/fragment shader 소스 코드를 검색합니다.
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ifstream 객체들이 예외를 던질 수 있도록 합니다.
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// 파일 열기
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// stream에 파일의 버퍼 내용을 읽기
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 파일 핸들러 닫기
		vShaderFile.close();
		fShaderFile.close();
		// stream을 string으로 변환
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
		// 오류가 발생한다면 컴파일 오류를 출력
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			TRACE0("\nVertex Shader 불러오는 데 문제 발생\n");
			// std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
	}
	// Fragment shader도 마찬가지
	{
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// 오류가 발생한다면 컴파일 오류를 출력
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			TRACE0("\nFragment Shader 불러오는 데 문제 발생\n");
			// std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
	}

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// 오류가 발생한다면 링킹 오류를 출력
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		// std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// program 내부에서 shader들이 링크 완료되었다면 이제 필요 없으므로 shader들을 삭제
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(ID); } // shader를 활성화하고 사용합니다 shader를 사용하려면 반드시 호출해야 합니다
// Uniform 유틸리티 함수들 Shader의 Uniform 변수에 값을 전달할때 사용합니다
void Shader::setfloat(const GLfloat& value, const std::string& str) const { glUniform1f(glGetUniformLocation(ID, str.c_str()), value); }
void Shader::setfloatv(const GLfloat* value, const int& size,const std::string& str) const { glUniform1fv(glGetUniformLocation(ID, str.c_str()), size, value); }
void Shader::setVec3(const glm::vec3& vec, const std::string& str) const { glUniform3fv(glGetUniformLocation(ID, str.c_str()), 1, glm::value_ptr(vec)); }
void Shader::setVec3v(const glm::vec3& vec, const int& size, const std::string& str) const { glUniform3fv(glGetUniformLocation(ID, str.c_str()), size, glm::value_ptr(vec)); }
void Shader::setVec4(const glm::vec4& vec, const std::string& str) const { glUniform4fv(glGetUniformLocation(ID, str.c_str()), 1, glm::value_ptr(vec)); }
void Shader::setMatirx3(const glm::mat4& matrix, const std::string& str) const { glUniformMatrix3fv(glGetUniformLocation(ID, str.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); }
void Shader::setMatrix4(const glm::mat4& matrix, const std::string& str) const { glUniformMatrix4fv(glGetUniformLocation(ID, str.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); }
void Shader::setUniform1i(const GLuint& i, const std::string& str) const { glUniform1i(glGetUniformLocation(ID, str.c_str()), i); }
void Shader::setUniform1f(const GLfloat& f, const std::string& str) const { glUniform1f(glGetUniformLocation(ID, str.c_str()), f); }
// Shader 객체의 Program ID를 받을때 사용합니다
GLuint Shader::getID(void) const { return ID; }
#pragma once
#include "Shader.h"

class Object
{
private:
	std::vector<GLfloat> vertex; // 정점들
	std::vector<GLubyte> index; // 정점 찍는 순서에 대한 인덱스
	GLuint id; // GenList의 id값
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float xX = 0.0f, yX = 0.0f, zX = 0.0f;
	float xRo = 0, yRo = 0, zRo = 0; // 회전 각도
	float xSc = 1, ySc = 1, zSc = 1; // Scale값
	// VAO와 VBO의 ID 값들입니다
	GLuint vaoId;
	GLuint vboVId;
	GLuint vboUvId;
	GLuint vboNorId;
	// Object 객체가 갖고있는 폴리곤의 수입니다
	int m_iNumTriangles = 0;
public:
	int objID = 0;


	std::vector<glm::vec3> bufferPosition; // Vertex의 위치
	std::vector<glm::vec2> bufferUV; // Vertex의 Texture 좌표
	std::vector<glm::vec3> bufferNormal; // Normal 좌표
	// 텍스쳐 + 재질 구조체
	typedef struct {
		GLuint textureId;
		glm::vec3 ambient = { 1.0f, 1.0f, 1.0f };
		glm::vec3 diffuse = { 1.0f, 1.0f, 1.0f };
		glm::vec3 specular = { 1.0f, 1.0f, 1.0f };
		GLfloat shininess;
		int w;
		int h;
		int comp;
		unsigned char* image = nullptr;
	} Texture;
	std::map<std::string, Texture> textures; // 여러 텍스쳐 저장한 구조체
	// Shape 구조체
	typedef struct {
		std::string texname;
		GLuint idxBegin;
		GLuint cntVertex;
	} Shape;
	std::vector<Shape> shapes;
public:
	void setObjPos(float x, float y, float z);
	void Draw(const Shader& shader); // Object 하나를 그립니다
	void setScale(const float& xSc, const float& ySc, const float& Sc); // Object의 Scale을 조정합니다
	void setNumTriangles(const int& n);
	void setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV);
};
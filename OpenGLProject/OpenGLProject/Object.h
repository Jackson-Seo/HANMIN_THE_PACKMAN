#pragma once
#include <vector>
#include <string>
#include <map>
#include "Shader.h"

class Object
{
private:
	std::vector<GLfloat> vertex; // ������
	std::vector<GLubyte> index; // ���� ��� ������ ���� �ε���
	GLuint id; // GenList�� id��
	float x = 0, y = 0, z = 0; // ���忡���� ��ġ
	float xRo = 0, yRo = 0, zRo = 0; // ȸ�� ����
	float xSc = 1, ySc = 1, zSc = 1; // Scale��
	// VAO�� VBO�� ID �����Դϴ�
	GLuint vaoId;
	GLuint vboVId;
	GLuint vboUvId;
	GLuint vboNorId;
	// Object ��ü�� �����ִ� �������� ���Դϴ�
	int m_iNumTriangles = 0;
public:
	std::vector<glm::vec3> bufferPosition; // Vertex�� ��ġ
	std::vector<glm::vec2> bufferUV; // Vertex�� Texture ��ǥ
	std::vector<glm::vec3> bufferNormal; // Normal ��ǥ
	// �ؽ��� ����ü
	typedef struct {
		GLuint textureId;
		int w;
		int h;
		int comp;
		unsigned char* image = nullptr;
	} Texture;
	std::map<std::string, Texture> textures; // ���� �ؽ��� ������ ����ü
	// Shape ����ü
	typedef struct {
		std::string texname;
		GLuint idxBegin;
		GLuint cntVertex;
	} Shape;
	std::vector<Shape> shapes;
public:
	void Draw(const Shader& shader); // Object �ϳ��� �׸��ϴ�
	void setScale(const float& xSc, const float& ySc, const float& Sc); // Object�� Scale�� �����մϴ�
	void setNumTriangles(const int& n);
	void setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV);
};
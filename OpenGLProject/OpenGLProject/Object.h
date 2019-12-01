#pragma once
#include "Shader.h"

class Object
{
private:
	std::vector<GLfloat> vertex; // ������
	std::vector<GLubyte> index; // ���� ��� ������ ���� �ε���
	GLuint id; // GenList�� id��
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float xX = 0.0f, yX = 0.0f, zX = 0.0f;
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
	int objID = 0;


	std::vector<glm::vec3> bufferPosition; // Vertex�� ��ġ
	std::vector<glm::vec2> bufferUV; // Vertex�� Texture ��ǥ
	std::vector<glm::vec3> bufferNormal; // Normal ��ǥ
	// �ؽ��� + ���� ����ü
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
	std::map<std::string, Texture> textures; // ���� �ؽ��� ������ ����ü
	// Shape ����ü
	typedef struct {
		std::string texname;
		GLuint idxBegin;
		GLuint cntVertex;
	} Shape;
	std::vector<Shape> shapes;
public:
	void setObjPos(float x, float y, float z);
	void Draw(const Shader& shader); // Object �ϳ��� �׸��ϴ�
	void setScale(const float& xSc, const float& ySc, const float& Sc); // Object�� Scale�� �����մϴ�
	void setNumTriangles(const int& n);
	void setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV);
};
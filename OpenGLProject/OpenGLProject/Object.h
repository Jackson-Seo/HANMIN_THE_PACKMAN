#pragma once
#include <vector>
#include <string>
#include <map>
#include "Shader.h"

using namespace std;

class Object
{
private:

	vector<GLfloat> vertex; // ������
	vector<GLubyte> index; // ���� ��� ������ ���� �ε���
	GLuint id; // GenList�� id��

	float x = 0, y = 0, z = 0; // ���忡���� ��ġ
	float xRo = 0, yRo = 0, zRo = 0; // ȸ�� ����
	float xSc = 1, ySc = 1, zSc = 1; // Scale��

	GLuint vaoId;
	GLuint vboVId;
	GLuint vboUvId;
	GLuint vboNorId;
	int m_iNumTriangles = 0;

public:

	vector<glm::vec3> bufferPosition; // Vertex�� ��ġ
	vector<glm::vec2> bufferUV; // Vertex�� Texture ��ǥ
	vector<glm::vec3> bufferNormal; // Normal ��ǥ
	// �ؽ��� ����ü
	typedef struct {
		GLuint textureId;
		int w;
		int h;
		int comp;
		unsigned char* image = nullptr;
	} Texture;
	map<string, Texture> textures; // ���� �ؽ��� ������ ����ü
	// Shape ����ü

	typedef struct {
		string texname;
		GLuint idxBegin;
		GLuint cntVertex;
	} Shape;
	vector<Shape> shapes;

public:
	void AddVertex(GLfloat vtx[], int size); // Object�� Vertex �߰�
	void AddIndex(GLubyte idx[], int size);
	void Draw(const Shader& shader); // Object�� �׸��ϴ�
	void setScale(const float& xSc, const float& ySc, const float& Sc); // Object�� Scale�� �����մϴ�
	void setNumTriangles(const int& n);
	void setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV);
};
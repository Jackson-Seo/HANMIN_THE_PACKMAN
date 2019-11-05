#pragma once
#include "pch.h"
#include <vector>

class Object
{
private:
	std::vector<GLfloat> vertex; // ������
	std::vector<GLubyte> index; // ���� ��� ������ ���� �ε���
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
	std::vector<glm::vec3> bufferPosition;
	std::vector<glm::vec2> bufferUV;
	std::vector<glm::vec3> bufferNormal;
	// �ؽ��� ����ü
	typedef struct {
		int w;
		int h;
		int comp;
		unsigned char* image = nullptr;
	} Texture;
	std::map<std::string, Texture> textures; // ���� �ؽ��� ������ ����ü
	// SubMesh ����ü
	typedef struct {
		std::string texname;
		GLuint textureId;
		GLuint idxBegin;
		GLuint cntVertex;
	} SubMesh;
	std::vector<SubMesh> subMeshs;
public:
	Object(void);
	Object(const GLuint id);
	~Object(void);
	void AddVertex(GLfloat vtx[], int size); // Object�� Vertex �߰�
	void AddIndex(GLubyte idx[], int size);
	void Draw(void); // Object�� �׸��ϴ� ��ȯ���� ó���մϴ�
	void setScale(const float& xSc, const float& ySc, const float& Sc); // Object�� Scale�� �����մϴ�
	void setNumTriangles(const int& n);
	void setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV);
};
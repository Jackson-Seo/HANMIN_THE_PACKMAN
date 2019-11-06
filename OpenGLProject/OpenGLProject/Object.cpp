#include "pch.h"
#include "Object.h"

Object::Object(void) {
	this->id = NULL;
}

Object::Object(const GLuint id) {
	this->id = id;
}

void Object::AddVertex(GLfloat vtx[], int size) {
	for (int i = 0; i < size; i++) {
		this->vertex.push_back(vtx[i]);
	}
}

void Object::AddIndex(GLubyte idx[], int size) {
	for (int i = 0; i < size; i++) {
		this->index.push_back(idx[i]);
	}
}

void Object::Draw(void) {
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vaoId);

	for (auto it = this->shapes.begin(); it != this->shapes.end(); ++it)
	{
		glBindTexture(GL_TEXTURE_2D, this->textures[it->texname].textureId);
		glUniform1i(glGetUniformLocation(ProgramId, "myTextureSampler"), 0);

		glDrawArrays(GL_TRIANGLES, it->idxBegin, it->cntVertex);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Object::setScale(const float& xSc, const float& ySc, const float& zSc) {
	this->xSc = xSc;
	this->ySc = ySc;
	this->zSc = zSc;
}

void Object::setNumTriangles(const int& n) { m_iNumTriangles = n; }
void Object::setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV) {
	vaoId = vao;
	vboVId = vboV;
	vboUvId = vboUV;
}
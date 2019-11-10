#include "pch.h"
#include "Object.h"

void Object::Draw(GLuint progId) {
	glm::mat4 mvp = glm::mat4(1.0f); // Identitiy 행렬 설정
	mvp = glm::translate(mvp, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate
	mvp = glm::rotate(mvp, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); // Rotate
	mvp = glm::scale(mvp, glm::vec3(0.5f, 0.5f, 0.5f)); // Scale

	glUniformMatrix4fv(glGetUniformLocation(progId, "model"), 1, GL_FALSE, glm::value_ptr(mvp));

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vaoId);

	for (auto it = this->shapes.begin(); it != this->shapes.end(); ++it)
	{
		if (it->texname == "") {
			continue;
		}
		glBindTexture(GL_TEXTURE_2D, this->textures[it->texname].textureId);
		glUniform1i(glGetUniformLocation(progId, "textureSampler"), 0);

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
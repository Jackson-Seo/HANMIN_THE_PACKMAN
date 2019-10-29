#include "pch.h"
#include "Object.h"

Object::Object(void) {

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
	glVertexPointer(3, GL_FLOAT, sizeof(this->vertex) / sizeof(this->vertex) / 3, &this->vertex);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(this->xRo, 1, 0, 0);
	glRotatef(this->yRo, 0, 1, 0);
	glRotatef(this->zRo, 0, 0, 1);
	glTranslatef(this->x, this->y, this->z);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, &this->index);
	glPopMatrix();
}
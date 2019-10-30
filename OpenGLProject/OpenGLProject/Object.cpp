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
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->xRo, 1, 0, 0);
	glRotatef(this->yRo, 0, 1, 0);
	glRotatef(this->zRo, 0, 0, 1);
	glScalef(this->xSc, this->ySc, this->zSc);
	glCallList(this->id);
	glPopMatrix();
}

void Object::setScale(const float& xSc, const float& ySc, const float& zSc) {
	this->xSc = xSc;
	this->ySc = ySc;
	this->zSc = zSc;
}
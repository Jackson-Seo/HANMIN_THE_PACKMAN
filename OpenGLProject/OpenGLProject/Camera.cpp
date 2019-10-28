#include "pch.h"
#include "Camera.h"

// �������� �ʱ�ȭ
CPoint Camera::s_CaRo = { 0, 0 };
CPoint Camera::s_CaTrans = { 0, 0 };

void Camera::Initialize() {
	// �ʱ� ī�޶� ��ġ�� �����մϴ�
	gluLookAt(0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void Camera::ReSize(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	// �������� ������ �ƴ� PROJECTION ����� ������ ���ο� ���� ����� ����ִ´�
	// ���ο� ���� ����� �������� ī�޶� ȸ���� �ϱ� ����
	glPopMatrix();
	glLoadIdentity();
	// calculate aspect ratio of the window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	// ���� ����� ����� �������� ��´�
	glPushMatrix();
	// ȥ���� �Ͼ�� �ʵ��� Matrix Mode�� ModelView�� �����մϴ�
	glMatrixMode(GL_MODELVIEW);
}

void Camera::Convert() {
	glMatrixMode(GL_PROJECTION);
	// ������ ��ȯ�� ����� ������ ���� ��ķ� �ٽ� ����Ѵ�
	glPopMatrix();
	// ���� ����� �� ���� ���� Push�Ѵ�
	glPushMatrix();
	// Camera�� ȸ����Ų��
	// ó�� ��ġ���� ���콺 ���������� ���� �̵��� ���� �������� ȸ����Ų��
	// Y���� �������� ȸ����Ų��
	glRotatef(s_CaRo.x * fCameraMovemet, 0, 1, 0);
	// Y���� ȸ���� ��ŭ X���� ȸ����Ű�� ȸ���� ��(XZ���)�� �������� ȸ����Ų��
	glRotatef(s_CaRo.y * fCameraMovemet, cosf(s_CaRo.x * fCameraMovemet * 3.141592 / 180), 0, sinf(s_CaRo.x * fCameraMovemet * 3.141592 / 180));
	// ȥ���� �Ͼ�� �ʵ��� Matrix Mode�� ModelView�� �����մϴ�
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setCaRo(CPoint point) {
	s_CaRo = point;
}
CPoint Camera::getCaRo() {
	return s_CaRo;
}
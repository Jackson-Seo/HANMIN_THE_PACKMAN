#include "pch.h"
#include "Camera.h"
#include "Controller.h"

// �������� �ʱ�ȭ
const float Camera::c_fCameraRotate = 0.2778f;
const float Camera::c_fCameraTrans = 0.05;
const float Camera::c_Degree = 3.141592 / 180;
CPoint Camera::s_CaRo = { 0, 0 };
float Camera::s_X = 0;
float Camera::s_Y = 0;
float Camera::s_Z = 0;

void Camera::Initialize() {
	// �ʱ� ī�޶� ��ġ�� �����մϴ�
	// -X �������� ī�޶� �ٶ���� ���߿� ī�޶� �̵��ÿ� ������ �Ȼ���ϴ�
	gluLookAt(3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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
	glRotatef(s_CaRo.x * c_fCameraRotate, 0, 1, 0);
	// Y���� ȸ���� ��ŭ X���� ȸ����Ű�� ȸ���� ��(XZ���)�� �������� ȸ����Ų��
	glRotatef(s_CaRo.y * c_fCameraRotate, cosf(s_CaRo.x * c_fCameraRotate * c_Degree), 0, sinf(s_CaRo.x * c_fCameraRotate * c_Degree));

	glMatrixMode(GL_MODELVIEW);
	// ������ ����� ����� �������� ������� Pop�ϰ�
	// �� ����� �����ϱ� ���� Push�մϴ�
	glPopMatrix();
	glPushMatrix();
	// ī�޶��� ��ġ��ŭ �����̵��մϴ�
	glTranslatef(s_X, s_Y, s_Z);
}

// x���� 1�̸� ������ �̵��ϰ� -1�̸� �ڷ� �̵��մϴ�
// z���� 1�̸� �������� �̵��ϰ� -1�̸� �������� �̵��մϴ�
void Camera::Move(int x, int y, int z) {
	// ī�޶��� ���� ������ �������� sin, cos ���� ����մϴ�
	float sinX = sinf(s_CaRo.x * c_fCameraRotate * c_Degree);
	float cosX = cosf(s_CaRo.x * c_fCameraRotate * c_Degree);
	float sinY = sinf(s_CaRo.y * c_fCameraRotate * c_Degree);
	float cosY = cosf(s_CaRo.y * c_fCameraRotate * c_Degree);
	s_X += (x * cosX - z * sinX) * cosY * c_fCameraTrans;
	s_Y += x * c_fCameraTrans * sinY;
	s_Z += (x * sinX + z * cosX) * cosY * c_fCameraTrans;
}

void Camera::setCaRo(CPoint point) {
	s_CaRo = point;
}
CPoint Camera::getCaRo() {
	return s_CaRo;
}
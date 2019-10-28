#include "pch.h"
#include "Camera.h"

// 정적변수 초기화
CPoint Camera::s_CaRo = { 0, 0 };
CPoint Camera::s_CaTrans = { 0, 0 };

void Camera::Initialize() {
	// 초기 카메라 위치를 지정합니다
	gluLookAt(0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void Camera::ReSize(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	// 이전까지 기준이 됐던 PROJECTION 행렬을 꺼내고 새로운 기준 행렬을 집어넣는다
	// 새로운 기준 행렬을 기준으로 카메라 회전을 하기 위함
	glPopMatrix();
	glLoadIdentity();
	// calculate aspect ratio of the window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	// 새로 계산한 행렬을 기준으로 삼는다
	glPushMatrix();
	// 혼동이 일어나지 않도록 Matrix Mode를 ModelView로 설정합니다
	glMatrixMode(GL_MODELVIEW);
}

void Camera::Convert() {
	glMatrixMode(GL_PROJECTION);
	// 이전에 변환된 행렬을 버리고 기준 행렬로 다시 계산한다
	glPopMatrix();
	// 기준 행렬을 또 쓰기 위해 Push한다
	glPushMatrix();
	// Camera를 회전시킨다
	// 처음 위치에서 마우스 움직임으로 누적 이동한 값을 기준으로 회전시킨다
	// Y축을 기준으로 회전시킨다
	glRotatef(s_CaRo.x * fCameraMovemet, 0, 1, 0);
	// Y축이 회전된 만큼 X축을 회전시키고 회전된 축(XZ평면)을 기준으로 회전시킨다
	glRotatef(s_CaRo.y * fCameraMovemet, cosf(s_CaRo.x * fCameraMovemet * 3.141592 / 180), 0, sinf(s_CaRo.x * fCameraMovemet * 3.141592 / 180));
	// 혼동이 일어나지 않도록 Matrix Mode를 ModelView로 설정합니다
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setCaRo(CPoint point) {
	s_CaRo = point;
}
CPoint Camera::getCaRo() {
	return s_CaRo;
}
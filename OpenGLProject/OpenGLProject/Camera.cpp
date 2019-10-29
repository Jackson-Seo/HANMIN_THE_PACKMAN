#include "pch.h"
#include "Camera.h"
#include "Controller.h"

// 정적변수 초기화
const float Camera::c_fCameraRotate = 0.2778f;
const float Camera::c_fCameraTrans = 0.05;
const float Camera::c_Degree = 3.141592 / 180;
CPoint Camera::s_CaRo = { 0, 0 };
float Camera::s_X = 0;
float Camera::s_Y = 0;
float Camera::s_Z = 0;

void Camera::Initialize() {
	// 초기 카메라 위치를 지정합니다
	// -X 방향으로 카메라가 바라봐야 나중에 카메라 이동시에 오류가 안생깁니다
	gluLookAt(3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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
	glRotatef(s_CaRo.x * c_fCameraRotate, 0, 1, 0);
	// Y축이 회전된 만큼 X축을 회전시키고 회전된 축(XZ평면)을 기준으로 회전시킨다
	glRotatef(s_CaRo.y * c_fCameraRotate, cosf(s_CaRo.x * c_fCameraRotate * c_Degree), 0, sinf(s_CaRo.x * c_fCameraRotate * c_Degree));

	glMatrixMode(GL_MODELVIEW);
	// 기존에 저장될 행렬을 기준으로 삼기위해 Pop하고
	// 이 행렬을 재사용하기 위해 Push합니다
	glPopMatrix();
	glPushMatrix();
	// 카메라의 위치만큼 평행이동합니다
	glTranslatef(s_X, s_Y, s_Z);
}

// x값이 1이면 앞으로 이동하고 -1이면 뒤로 이동합니다
// z값이 1이면 우측으로 이동하고 -1이면 좌측으로 이동합니다
void Camera::Move(int x, int y, int z) {
	// 카메라의 현재 각도를 기준으로 sin, cos 값을 계산합니다
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
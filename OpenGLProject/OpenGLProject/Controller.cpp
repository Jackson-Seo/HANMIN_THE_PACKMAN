#include "pch.h"
#include "Controller.h"
#include "Camera.h"

// 정적변수 초기화
clock_t Controller::time = 0.0;
clock_t Controller::deltaTime = 0.0;
bool Controller::bRClick = FALSE;
bool Controller::bLClick = FALSE;
CPoint Controller::clickPoint = { 0, 0 };
CPoint Controller::preClickPoint = { 0, 0 };

// OpenGLProjectView의 initGL에서 호출시켜 초기화 시킵니다
void Controller::Initialize(void) {
	time = clock();
}

/*
	OpenGLProjectView의 DrawGLScene에서 호출시켜 프레임간 시간차를 계산합니다
	마우스가 움직인 거리만큼 카메라를 회전시킵니다
*/
void Controller::Clock(void) {
	clock_t newTime = clock();
	deltaTime = newTime - time;
	time = newTime;
	// TRACE1("%lf\n", (double)deltaTime);
	
	// deltaTime만큼 회전시키려 했으나 deltaTime이 제대로 계산이 안되므로 상수값을 넘겨줍니다
	Camera::Rotate(clickPoint, 1.3f);
	clickPoint = { 0, 0 };
}

void Controller::OnMouseMove(UINT nFlags, CPoint point)
{
	/*
		if문 : 우클릭이 된 상태에서 드래그가 일어났는가?
		TRUE : 마우스가 누적 이동한 거리를 계산합니다
	*/
	if (bRClick) {
		clickPoint += point - preClickPoint;
		preClickPoint = point;
	}
}

void Controller::OnRButtonDown(UINT nFlags, CPoint point)
{
	bRClick = true;
	clickPoint = { 0, 0 };
	preClickPoint = point;
}

void Controller::OnRButtonUp(UINT nFlags, CPoint point)
{
	bRClick = false;
}
// 입력된 키에 따라서 카메라를 해당 방향으로 움직입니다
void Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case 'W':
		Camera::Move(Direction::FORWARD, (double)deltaTime);
		break;
	case 'A':
		Camera::Move(Direction::LEFT, (double)deltaTime);
		break;
	case 'S':
		Camera::Move(Direction::BACKWARD, (double)deltaTime);
		break;
	case 'D':
		Camera::Move(Direction::RIGHT, (double)deltaTime);
		break;
	case 'Q':
		Camera::Move(Direction::UP, (double)deltaTime);
		break;
	case 'E':
		Camera::Move(Direction::DOWN, (double)deltaTime);
		break;
	}
}
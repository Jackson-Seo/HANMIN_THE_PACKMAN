#include "pch.h"
#include "Controller.h"
#include "Camera.h"

// 정적변수 초기화
time_t Controller::time = 0.0;
time_t Controller::deltaTime = 0.0;
bool Controller::bRClick = FALSE;
bool Controller::bLClick = FALSE;
CPoint Controller::clickPoint = { 0, 0 };
CPoint Controller::preClickPoint = { 0, 0 };

void Controller::Initialize(void) {
	time = clock();
}

void Controller::Clock(void) {
	deltaTime = clock() - time;
	time = clock();
}

void Controller::OnMouseMove(UINT nFlags, CPoint point)
{
	if (bRClick) {
		Camera::Rotate(point - clickPoint, (double)deltaTime);
		clickPoint = point;
	}
}

void Controller::OnRButtonDown(UINT nFlags, CPoint point)
{
	bRClick = true;
	clickPoint = point;
}

void Controller::OnRButtonUp(UINT nFlags, CPoint point)
{
	bRClick = false;
}

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
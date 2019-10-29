#include "pch.h"
#include "Controller.h"
#include "Camera.h"

// 정적변수 초기화
const float Controller::c_fCameraTrans = 0.05;
bool Controller::s_bRClick = FALSE;
bool Controller::s_bLClick = FALSE;
CPoint Controller::s_ClickPoint = { 0, 0 };
CPoint Controller::s_preClickPoint = { 0, 0 };
bool Controller::s_bW = FALSE;
bool Controller::s_bA = FALSE;
bool Controller::s_bS = FALSE;
bool Controller::s_bD = FALSE;

// W는 앞 A는 좌 S는 뒤 D는 우
void Controller::CameraTrans() {
	if (s_bW) {
		Camera::Move(c_fCameraTrans, 0, 0);
	}
	if (s_bA) {
		Camera::Move(0, 0, -c_fCameraTrans);
	}
	if (s_bS) {
		Camera::Move(-c_fCameraTrans, 0, 0);
	}
	if (s_bD) {
		Camera::Move(0, 0, c_fCameraTrans);
	}
}

void Controller::setRClick(bool b) {
	s_bRClick = b;
}
bool Controller::getRClick() {
	return s_bRClick;
}
void Controller::setLClick(bool b) {
	s_bLClick = b;
}
bool Controller::getLClick() {
	return s_bLClick;
}
void Controller::setClickPoint(CPoint point) {
	s_ClickPoint = point;
}
CPoint Controller::getClickPoint() {
	return s_ClickPoint;
}
void Controller::setpreClickPoint(CPoint point) {
	s_preClickPoint = point;
}
CPoint Controller::getpreClickPoint() {
	return s_preClickPoint;
}
void Controller::setW(bool b) {
	s_bW = b;
}
bool Controller::getW() {
	return s_bW;
}
void Controller::setA(bool b) {
	s_bA = b;
}
bool Controller::getA() {
	return s_bA;
}
void Controller::setS(bool b) {
	s_bS = b;
}
bool Controller::getS() {
	return s_bS;
}
void Controller::setD(bool b) {
	s_bD = b;
}
bool Controller::getD() {
	return s_bD;
}
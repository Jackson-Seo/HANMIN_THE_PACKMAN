#include "pch.h"
#include "Controller.h"
#include "Camera.h"

// 정적변수 초기화
bool Controller::s_bRClick = FALSE;
bool Controller::s_bLClick = FALSE;
CPoint Controller::s_ClickPoint = { 0, 0 };
CPoint Controller::s_preClickPoint = { 0, 0 };

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
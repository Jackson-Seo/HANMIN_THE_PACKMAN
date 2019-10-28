#include "pch.h"
#include "Controller.h"

BOOL Controller::s_bRClick = FALSE;
BOOL Controller::s_bLClick = FALSE;
CPoint Controller::s_ClickPoint = { 0, 0 };
CPoint Controller::s_preClickPoint = { 0, 0 };

void Controller::setRClick(BOOL b) {
	s_bRClick = b;
}
BOOL Controller::getRClick() {
	return s_bRClick;
}
void Controller::setLClick(BOOL b) {
	s_bLClick = b;
}
BOOL Controller::getLClick() {
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
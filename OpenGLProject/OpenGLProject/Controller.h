#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static bool s_bRClick; // 마우스 우클릭 감지
	static bool s_bLClick; // 마우스 좌클릭 감지
	static CPoint s_ClickPoint; // 마우스 클릭 위치
	static CPoint s_preClickPoint; // 마우스 이동에서 이전 이동 위치
	static bool s_bW; // W키 감지
	static bool s_bA; // A키 감지
	static bool s_bS; // S키 감지
	static bool s_bD; // D키 감지
public:
	static void CameraTrans(); // WASD 키에 따라 카메라를 평행이동 합니다
public:
	static void setRClick(bool b);
	static bool getRClick();
	static void setLClick(bool b);
	static bool getLClick();
	static void setClickPoint(CPoint point);
	static CPoint getClickPoint();
	static void setpreClickPoint(CPoint point);
	static CPoint getpreClickPoint();
	static void setW(bool b);
	static bool getW();
	static void setA(bool b);
	static bool getA();
	static void setS(bool b);
	static bool getS();
	static void setD(bool b);
	static bool getD();
};


#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static BOOL s_bRClick; // 마우스 우클릭 감지
	static BOOL s_bLClick; // 마우스 좌클릭 감지
	static CPoint s_ClickPoint; // 마우스 클릭 위치
	static CPoint s_preClickPoint; // 마우스 이동에서 이전 이동 위치
public:
	static void setRClick(BOOL b);
	static BOOL getRClick();
	static void setLClick(BOOL b);
	static BOOL getLClick();
	static void setClickPoint(CPoint point);
	static CPoint getClickPoint();
	static void setpreClickPoint(CPoint point);
	static CPoint getpreClickPoint();
};


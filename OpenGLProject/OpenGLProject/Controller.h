#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static time_t time;
	static time_t deltaTime; // 프레임간 시간 차이
	static bool bRClick; // 마우스 우클릭 감지
	static bool bLClick; // 마우스 좌클릭 감지
	static CPoint clickPoint; // 마우스 클릭 위치
	static CPoint preClickPoint; // 마우스 이동에서 이전 이동 위치
public:
	static void Initialize(void);
	static void Clock(void);
public:
	static void OnMouseMove(UINT nFlags, CPoint point);
	static void OnRButtonDown(UINT nFlags, CPoint point);
	static void OnRButtonUp(UINT nFlags, CPoint point);
	static void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

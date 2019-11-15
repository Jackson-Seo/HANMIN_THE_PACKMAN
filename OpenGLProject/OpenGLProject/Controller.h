#pragma once
#include <afxwin.h>
/*
	마우스 및 키보드 같은 컨트롤 처리는 이 클래스에서 다룹니다
	MFC에서 메시지를 바로 받기위해 CWnd를 상속했지만 현재는 되지 않습니다
	메시지를 바로 받을 수 없으므로 메시지는 OpenGLProjectView.cpp에서 받고 거기서 이 클래스를 호출합니다
*/
class Controller : public CWnd
{
private:
	static clock_t time; // deltaTime을 계산하기 위해 이전의 time_t를 저장
	static clock_t deltaTime; // 프레임간 시간 차이
	static bool bRClick; // 마우스 우클릭 감지
	static bool bLClick; // 마우스 좌클릭 감지
	static CPoint clickPoint; // 마우스가 누적해서 이동한 거리
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

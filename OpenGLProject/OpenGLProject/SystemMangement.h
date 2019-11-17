//월드 전체의 시간과 tick per frame 을 관리합니다. (Controller 의 clock() 함수를 여기로 이동했음)
//내부 메모리 관리를 책임집니다.

#pragma once
#include <afxwin.h>

class _SystemMangement_
{
public:
	static clock_t time; // deltaTime을 계산하기 위해 이전의 time_t를 저장
	static clock_t deltaTime; // 프레임간 시간 차이
	static bool bCameraOn;     //카메라 모드 on/off
	static bool bObjectOn;     // 오브젝트 이동 on/off
	static bool blightOn;      // 라이트 이동 on/off

public:

	static void initSystem(void);
	static void Clock(void);
};

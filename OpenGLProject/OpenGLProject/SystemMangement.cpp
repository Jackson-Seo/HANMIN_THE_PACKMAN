#include "pch.h"
#include "SystemMangement.h"

clock_t _SystemMangement_::time = 0.0;
clock_t _SystemMangement_::deltaTime = 0.0;

bool _SystemMangement_::bCameraOn = true;
bool _SystemMangement_::bObjectOn = false;
bool _SystemMangement_::blightOn = false;

float _SystemMangement_::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}

void _SystemMangement_::Clock(void)
{
	clock_t newTime = clock();
	deltaTime = newTime - time;
	time = newTime;
	// TRACE1("%lf\n", (double)deltaTime);
}
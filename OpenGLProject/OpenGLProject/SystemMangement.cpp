#include "pch.h"
#include "SystemMangement.h"

clock_t _SystemMangement_::time = 0.0;
clock_t _SystemMangement_::deltaTime = 0.0;

bool _SystemMangement_::bCameraOn = true;
bool _SystemMangement_::bObjectOn = false;
bool _SystemMangement_::blightOn = false;


void _SystemMangement_::Clock(void)
{
	clock_t newTime = clock();
	deltaTime = newTime - time;
	time = newTime;
	// TRACE1("%lf\n", (double)deltaTime);
}

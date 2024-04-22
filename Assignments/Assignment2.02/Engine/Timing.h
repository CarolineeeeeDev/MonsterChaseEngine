#pragma once
#include <Windows.h>

namespace Engine
{
	class TimingComponent
	{
	public:
		bool isFirstTick = true;
		LARGE_INTEGER lastFrameTime = {0} ;
		void GetCurrentCPUCounter(LARGE_INTEGER& counter);
		float CalculateTimeSinceLastCall();
	};
}

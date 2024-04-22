#include "Timing.h"

namespace Engine
{
	void TimingComponent::GetCurrentCPUCounter(LARGE_INTEGER& counter)
	{
		QueryPerformanceCounter(&counter);
	}
	float TimingComponent::CalculateTimeSinceLastCall()
	{
		LARGE_INTEGER currentFrameTime;
		GetCurrentCPUCounter(currentFrameTime);
		if (isFirstTick)
		{
			isFirstTick = false;
			lastFrameTime = currentFrameTime;
			return 0.016f;
		}
		LARGE_INTEGER ticksPerSecond;
		QueryPerformanceFrequency(&ticksPerSecond);
		float dt = (float)(currentFrameTime.QuadPart - lastFrameTime.QuadPart) / (float)ticksPerSecond.QuadPart*100.0f;
		lastFrameTime = currentFrameTime;
		return dt;
	}
}

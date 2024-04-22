#pragma once
#include <Windows.h>
#include "Component.h"
namespace Engine
{
	class TimingComponent : public Component
	{
	public:
		TimingComponent() = default;

		float dt = 0.0f;
		bool isFirstTick = true;
		LARGE_INTEGER lastFrameTime = { 0 };
		void GetCurrentCPUCounter(LARGE_INTEGER& counter);
		float CalculateTimeSinceLastCall();
		void update();
	};
}

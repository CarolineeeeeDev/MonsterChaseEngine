#pragma once
#include "Types.h"
#include "Component.h"

namespace Engine
{
	class AIComponent : public Component
	{
	public:
		AIComponent() = default;

		bool upDownFlag = false;
		bool leftRightFlag = false;
		void Run();
		void update();
	};
}
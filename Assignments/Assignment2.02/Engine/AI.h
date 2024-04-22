#pragma once
#include "Types.h"

namespace Engine
{
	class AIComponent
	{
	public:
		bool upDownFlag = false;
		bool leftRightFlag = false;
		void Run(float dt, int numMonsters, Monster** monsters);
	};
}
#pragma once
#include "GLib.h"
#include "Types.h"
#include <vector>


namespace Engine
{
	class RendererComponent
	{
	public:

		void Draw(GameSprites* gamesprites, int numMonsters, Monster** monsters, Player* player);
	};
}
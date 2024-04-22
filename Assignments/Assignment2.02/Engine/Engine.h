#pragma once
#include "GLib.h"
#include "Types.h"
#include "AI.h"
#include "Timing.h"
#include "Physics.h"
#include "Renderer.h"
#include <Windows.h>


namespace Engine
{
	class MonsterChaseEngine
	{
	public:
		TimingComponent* timer ;
		AIComponent* ai ;
		PhysicsComponent* physics;
		RendererComponent* renderer;
		MonsterChaseEngine(TimingComponent* _timer, AIComponent* _ai, PhysicsComponent* _physics, RendererComponent* _renderer) :
			timer(_timer), ai(_ai), physics(_physics), renderer(_renderer){}
	};

	static MonsterChaseEngine* monsterChaseEngine = new MonsterChaseEngine(new TimingComponent(),new AIComponent(), new PhysicsComponent(), new RendererComponent());
	void Run(int numMonsters, Monster** monsters, Player* player, GameSprites* gamesprites);
}

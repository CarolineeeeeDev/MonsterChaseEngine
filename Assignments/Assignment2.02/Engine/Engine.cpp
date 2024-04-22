#pragma once
#include "Engine.h"



void Engine::Run(int numMonsters, Monster** monsters, Player* player, GameSprites* gamesprites)
{
	
	float dt = monsterChaseEngine->timer->CalculateTimeSinceLastCall();
	monsterChaseEngine->ai->Run(dt, numMonsters, monsters);
	monsterChaseEngine->physics->Run(dt, player);
	monsterChaseEngine->renderer->Draw(gamesprites,numMonsters, monsters, player);
}
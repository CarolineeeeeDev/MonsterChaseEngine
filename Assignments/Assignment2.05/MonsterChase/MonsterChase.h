#pragma once
#include <memory>
#include "Types.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Timing.h"
#include "Physics.h"
#include "AI.h"
#include "Renderer.h"

using namespace std;

int numMonsters = 0;
bool isGameOver;
bool bQuit;
std::shared_ptr<EntityManager> manager;

void InitiatePlayerEntity();
void UpdatePlayerPos(unsigned int i_VKeyID, bool bWentDown);

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
GLib::Sprite* CreateSprite(const char* i_pFilename);
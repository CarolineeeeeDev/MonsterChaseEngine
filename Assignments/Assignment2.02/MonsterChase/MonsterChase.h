#pragma once
#include "Types.h"

using namespace std;



int numMonsters = 0;
Monster** monsters;
Player* player;
GameSprites* gamesprites;

Monster** InitiateMonster();

void UpdatePlayerPos(unsigned int i_VKeyID, bool bWentDown);

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
GLib::Sprite* CreateSprite(const char* i_pFilename);
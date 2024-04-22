#pragma once
#include "Types.h"
#define GRID_SIZE 10

using namespace std;


GLib::Sprite* pPlayer;
GLib::Sprite* pMonster;
GLib::Sprite* pControl;
GLib::Sprite* pTitle;
GLib::Sprite* pGameOver;

int numMonsters = 0;
Monster** monsters;
Player* player;

Monster** InitiateMonster();

void UpdatePlayerPos(unsigned int i_VKeyID, bool bWentDown);
void UpdateMonsterPos(unsigned int i_VKeyID, bool bWentDown);

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
GLib::Sprite* CreateSprite(const char* i_pFilename);
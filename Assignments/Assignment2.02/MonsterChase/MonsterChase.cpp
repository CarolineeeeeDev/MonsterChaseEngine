#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <DirectXColors.h>

#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG


#include "GLib.h"
#include "Engine.h"
#include "MonsterChase.h"



void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG


	UpdatePlayerPos(i_VKeyID, bWentDown);

}

void UpdatePlayerPos(unsigned int i_VKeyID, bool bWentDown)
{
	if (bWentDown == true)
	{
		if (i_VKeyID == 0x51) //Q
		{
			exit(0);
		}
		else {
			if (!player->isGameOver)
			{
				if (i_VKeyID == 0x57) {//W
					player->drivingForce2D = Engine::Point2D(0, 2.0f);
				}
				else if (i_VKeyID == 0x53) {//S
					player->drivingForce2D = Engine::Point2D(0, -2.0f);
				}
				else if (i_VKeyID == 0x41) {//A
					player->drivingForce2D = Engine::Point2D(-2.0f, 0);
				}
				else if (i_VKeyID == 0x44) {//D
					player->drivingForce2D = Engine::Point2D(2.0f, 0);
				}

			}
		}

	}
}


Monster** InitiateMonster() {
	Monster** monstersList = new Monster * [numMonsters];
	default_random_engine e(static_cast<unsigned int> (time(0)));
	for (int i = 0; i < numMonsters; i++)
	{
		monstersList[i] = new Monster(Engine::Point2D(-(float)(e() % 500), -(float)(e() % 500)));
	}
	return monstersList;
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	numMonsters = 4;
	player = new Player("Player", Engine::Point2D(-500.0f, -500.0f), false, false, Engine::Point2D(0, 0));
	monsters = InitiateMonster();

	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 1200, true);

	if (bSuccess)
	{
		GLib::SetKeyStateChangeCallback(TestKeyCallback);
		gamesprites = new GameSprites(CreateSprite("data\\Player.dds"), CreateSprite("data\\Monster.dds"), CreateSprite("data\\Control.dds"), CreateSprite("data\\Title.dds"), CreateSprite("data\\GameOver.dds"));
		player->bQuit = false;

		while (player->bQuit == false)
		{
			Engine::Run(numMonsters, monsters, player, gamesprites);
		} 
		

		if (gamesprites->pPlayer)
			GLib::Release(gamesprites->pPlayer);
		if (gamesprites->pMonster)
			GLib::Release(gamesprites->pMonster);
		if (gamesprites->pControl)
			GLib::Release(gamesprites->pControl);
		if (gamesprites->pTitle)
			GLib::Release(gamesprites->pTitle);
		if (gamesprites->pGameOver)
			GLib::Release(gamesprites->pGameOver);


		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}

GLib::Sprite* CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return nullptr;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(*pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::SpriteEdges	Edges = { -float(width / 8.0f), float(height / 2.0f), float(width / 4.0f), 0.0f };
	GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

	// release our reference on the Texture
	GLib::Release(pTexture);

	return pSprite;
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

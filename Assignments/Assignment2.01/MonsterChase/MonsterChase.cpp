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
	UpdateMonsterPos(i_VKeyID, bWentDown);

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
					if (player->position.y < GRID_SIZE - 1)
						player->position += Engine::Point2D(0, 1);

				}
				else if (i_VKeyID == 0x53) {//S
					if (player->position.y > 0)
						player->position += Engine::Point2D(0, -1);
				}
				else if (i_VKeyID == 0x41) {//A
					if (player->position.x > 0)
						player->position += Engine::Point2D(-1, 0);
				}
				else if (i_VKeyID == 0x44) {//D
					if (player->position.x < GRID_SIZE - 1)
						player->position += Engine::Point2D(1, 0);
				}

			}
		}

	}
}

void UpdateMonsterPos(unsigned int i_VKeyID, bool bWentDown) {
	if (!player->isGameOver)
	{
		if (bWentDown == true)
		{
			if ((i_VKeyID == 0x57) || (i_VKeyID == 0x53) || (i_VKeyID == 0x41) || (i_VKeyID == 0x44))
			{
				for (int i = 0; i < numMonsters; ++i) {
					int direction = rand() % 4; // 0: Down, 1: Up, 2: Left, 3: Right

					Engine::Point2D newPosition = monsters[i]->position;

					if (direction == 0 && newPosition.x >= 0) {
						newPosition += Engine::Point2D(0, -1); // Move down
					}
					else if (direction == 1 && newPosition.x <= GRID_SIZE - 1) {
						newPosition += Engine::Point2D(0, 1); // Move up
					}
					else if (direction == 2 && newPosition.y >= 0) {
						newPosition += Engine::Point2D(-1, 0); // Move left
					}
					else if (direction == 3 && newPosition.y <= GRID_SIZE - 1) {
						newPosition += Engine::Point2D(1, 0); // Move right
					}

					newPosition.x = max(0, min(GRID_SIZE - 1, newPosition.x));
					newPosition.y = max(0, min(GRID_SIZE - 1, newPosition.y));

					monsters[i]->position = newPosition; // Update the monster's position
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
		monstersList[i] = new Monster(Engine::Point2D(e() % GRID_SIZE, e() % GRID_SIZE));
		while ((monstersList[i]->position.x == 0) && (monstersList[i]->position.y == 0))
		{
			monstersList[i] = new Monster(Engine::Point2D(e() % GRID_SIZE, e() % GRID_SIZE));
		}
	}
	return monstersList;
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	numMonsters = 3;
	player = new Player("Player", Engine::Point2D(0, 0), false, false, Engine::Point2D(0, 0));
	monsters = InitiateMonster();

	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 1200, true);

	if (bSuccess)
	{
		GLib::SetKeyStateChangeCallback(TestKeyCallback);
		pPlayer = CreateSprite("data\\Player.dds");
		pMonster = CreateSprite("data\\Monster.dds");
		pControl = CreateSprite("data\\Control.dds");
		pTitle = CreateSprite("data\\Title.dds");
		pGameOver = CreateSprite("data\\GameOver.dds");

		bool bQuit = false;

		do
		{
			GLib::Service(bQuit);

			if (!bQuit)
			{
				GLib::BeginRendering(DirectX::Colors::Black);
				GLib::Sprites::BeginRendering();

				if (pTitle)
				{
					static GLib::Point2D TitlePosition = { -150.0f,550.0f };
					GLib::Render(*pTitle, TitlePosition, 0.0f, 0.0f);
				}
				if (pControl)

				{
					static GLib::Point2D ControlPosition = { -50.0f,-600.0f };
					GLib::Render(*pControl, ControlPosition, 0.0f, 0.0f);
				}
				if (pPlayer)
				{
					static GLib::Point2D Offset = { (float)(player->position.x * 100 - 500), (float)(player->position.y * 100 - 500) };
					Offset.x = (float)(player->position.x * 100 - 500);
					Offset.y = (float)(player->position.y * 100 - 500);
					GLib::Render(*pPlayer, Offset, 0.0f, 0.0f);

				}
				if (pMonster)
				{
					std::vector<GLib::Point2D> Offsets(numMonsters);
					for (int i = 0; i < numMonsters; i++)
					{
						Offsets[i] = { monsters[i]->position.x * 100.0f - 500, monsters[i]->position.y * 100.0f - 500 };
						Offsets[i].x = (float)(monsters[i]->position.x * 100.0f - 500);
						Offsets[i].y = (float)(monsters[i]->position.y * 100.0f - 500);
						GLib::Render(*pMonster, Offsets[i], 0.0f, 0.0f);
					}
				}
				if (pPlayer && pMonster && pGameOver)
				{
					for (int i = 0; i < numMonsters; i++)
					{
						if (player->position == monsters[i]->position)
						{
							player->isGameOver = true;
							static GLib::Point2D GameOverPosition = { -50.0f,-50.0f };
							GLib::Render(*pGameOver, GameOverPosition, 0.0f, 0.0f);
						}
					}
				}
				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (pPlayer)
			GLib::Release(pPlayer);
		if (pMonster)
			GLib::Release(pMonster);
		if (pControl)
			GLib::Release(pControl);
		if (pTitle)
			GLib::Release(pTitle);
		if (pGameOver)
			GLib::Release(pGameOver);


		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
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

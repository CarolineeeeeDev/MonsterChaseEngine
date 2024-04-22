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

#include "PlayerController.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectFactory.h"

#include "GLib.h"
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
			if (!isGameOver)
			{
				if (i_VKeyID == 0x57) {//W
					manager->entities[0]->drivingForce2D = Engine::Point2D(0, 2.0f);
				}
				else if (i_VKeyID == 0x53) {//S
					manager->entities[0]->drivingForce2D = Engine::Point2D(0, -2.0f);
				}
				else if (i_VKeyID == 0x41) {//A
					manager->entities[0]->drivingForce2D = Engine::Point2D(-2.0f, 0);
				}
				else if (i_VKeyID == 0x44) {//D
					manager->entities[0]->drivingForce2D = Engine::Point2D(2.0f, 0);
				}
			}


		}

	}
}

void InitiatePlayerEntity()
{

	std::shared_ptr<Entity> playerEntity = std::make_shared<Entity>();
	playerEntity->id = 0;
	playerEntity->sprite = CreateSprite("data\\Player.dds");
	playerEntity->position = Engine::Point2D(-500.0f, -500.0f);
	playerEntity->AddComponent<Engine::TimingComponent>();
	playerEntity->AddComponent<Engine::PhysicsComponent>();
	playerEntity->AddComponent<Engine::RendererComponent>();
	manager->addEntity(playerEntity);
}
void InitiateMonsterEntity(int numMonsters)
{
	default_random_engine e(static_cast<unsigned int> (time(0)));
	for (int i = 0; i < numMonsters; i++)
	{

		std::shared_ptr<Entity> monsterEntity = std::make_shared<Entity>();
		monsterEntity->id = i + 1;
		monsterEntity->position = Engine::Point2D(-(float)(e() % 500), -(float)(e() % 500));
		monsterEntity->sprite = CreateSprite("data\\Monster.dds");
		monsterEntity->AddComponent<Engine::AIComponent>();
		monsterEntity->AddComponent<Engine::RendererComponent>();
		manager->addEntity(monsterEntity);
	}
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	isGameOver = false;
	numMonsters = 4;
	manager = std::make_shared<EntityManager>();

	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 1200, true);

	if (bSuccess)
	{
		using namespace Engine;

		GameObjectFactory::RegisterControllerCreator("player", &PlayerController::Create);
		std::shared_ptr<GameObject> pNewGameObject(GameObjectFactory::CreateGameObject("data\\Player.json"));
		InitiatePlayerEntity();
		InitiateMonsterEntity(numMonsters);

		bQuit = false;
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		while (bQuit == false)
		{
			manager->update(bQuit,isGameOver, manager);
		} 
		

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

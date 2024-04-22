#include "Renderer.h"
#include <DirectXColors.h>

namespace Engine
{
	void RendererComponent::Draw(GameSprites* gamesprites, int numMonsters, Monster** monsters, Player* player)
	{
        GLib::Service(player->bQuit);
        if (!player->bQuit)
        {
            GLib::BeginRendering(DirectX::Colors::Black);
            GLib::Sprites::BeginRendering();
            if (gamesprites->pTitle)
            {
                static GLib::Point2D TitlePosition = { -150.0f,550.0f };
                GLib::Render(*gamesprites->pTitle, TitlePosition, 0.0f, 0.0f);
            }
            if (gamesprites->pControl)
            {
                static GLib::Point2D ControlPosition = { -50.0f,-600.0f };
                GLib::Render(*gamesprites->pControl, ControlPosition, 0.0f, 0.0f);
            }
            if (gamesprites->pPlayer)
            {
                static GLib::Point2D Offset = { player->position.x, player->position.y };
                Offset.x = player->position.x;
                Offset.y = player->position.y;
                GLib::Render(*gamesprites->pPlayer, Offset, 0.0f, 0.0f);

            }
            if (gamesprites->pMonster)
            {
                vector<GLib::Point2D> Offsets(numMonsters);
                for (int i = 0; i < numMonsters; i++)
                {
                    Offsets[i] = { monsters[i]->position.x , monsters[i]->position.y };
                    Offsets[i].x = monsters[i]->position.x;
                    Offsets[i].y = monsters[i]->position.y;
                    GLib::Render(*gamesprites->pMonster, Offsets[i], 0.0f, 0.0f);
                }
            }

            GLib::Sprites::EndRendering();
            GLib::EndRendering();
        }
	}
}
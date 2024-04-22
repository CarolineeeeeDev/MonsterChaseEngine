#include "Renderer.h"
#include "Entity.h"

#include <DirectXColors.h>
using namespace std;
namespace Engine
{
	void RendererComponent::Draw(bool bQuit)
	{
        

	}

    void RendererComponent::update(bool bQuit, std::shared_ptr<EntityManager> manager)
    {
        GLib::Service(bQuit);
        if (!bQuit)
        {
            GLib::BeginRendering(DirectX::Colors::Black);
            GLib::Sprites::BeginRendering();
            
            for (std::shared_ptr<Entity> entity : manager->entities)
            {
                if (entity->sprite)
                {
                    static GLib::Point2D Offset = { entity->position.x, entity->position.y };
                    Offset.x = entity->position.x;
                    Offset.y = entity->position.y;
                    GLib::Render(*entity->sprite, Offset, 0.0f, 0.0f);
                }
                
            }
            
            GLib::Sprites::EndRendering();
            GLib::EndRendering();
        }
    }
}


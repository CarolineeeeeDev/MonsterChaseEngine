#include "EntityManager.h"
#include "Timing.h"
#include "Physics.h"
#include "AI.h"
#include "Renderer.h"



void EntityManager::update(bool bQuit,bool isGameOver, EntityManager* manager)
{
	for (Entity* entity : entities)
	{

		if (entity->hasComponent<Engine::TimingComponent>())
		{
			entity->GetComponent<Engine::TimingComponent>().Engine::TimingComponent::update();
		}
		if (entity->hasComponent<Engine::PhysicsComponent>())
		{
			entity->GetComponent<Engine::PhysicsComponent>().Engine::PhysicsComponent::update();
		}
		if (entity->hasComponent<Engine::AIComponent>())
		{
			entity->GetComponent<Engine::AIComponent>().Engine::AIComponent::update();
		}
	}
	Engine::RendererComponent* render = new Engine::RendererComponent();
	render->update(bQuit, manager);

}

void EntityManager::addEntity(Entity* gameObject)
{
	entities.insert(entities.end(), gameObject);
}

void EntityManager::eraseEntity(Entity* gameObject)
{
}


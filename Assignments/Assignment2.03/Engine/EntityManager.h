#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
class Entity;
class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	void update(bool bQuit, bool isGameOver, EntityManager* manager);

	void addEntity(Entity* gameObject);
	void eraseEntity(Entity* gameObject);

	std::vector<Entity*> entities;
};
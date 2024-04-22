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

	void update(bool bQuit, bool isGameOver, std::shared_ptr<EntityManager> manager);

	void addEntity(std::shared_ptr<Entity> gameObject);
	void eraseEntity(std::shared_ptr<Entity> gameObject);

	std::vector<std::shared_ptr<Entity>> entities;
};
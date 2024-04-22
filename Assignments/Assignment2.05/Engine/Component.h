#pragma once
#include <memory>
class Entity;
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	virtual bool init() { return true; }
	virtual void draw() {}
	virtual void update() {}
};


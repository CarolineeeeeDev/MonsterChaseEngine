#pragma once
#include "ECS.h"
#include <vector>
#include <memory>
#include "Component.h"
#include "Types.h"

class Entity
{
public:
	Entity() = default;
	virtual ~Entity() = default;

	int id = -1;
	Engine::Point2D position = Engine::Point2D(0.0f, 0.0f);
	Engine::Point2D drivingForce2D = Engine::Point2D(0.0f, 0.0f);
	GLib::Sprite* sprite;
	ComponentList compList;
	ComponentBitset compBitset;
	std::vector<Component*> components;

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args)
	{
		T* comp(new T(std::forward(TArgs)(args)...));

		components.insert(components.end(), comp);

		if (comp->init())
		{
			compList[GetComponentTypeID<T>()] = comp;
			compBitset[GetComponentTypeID<T>()] = true;
			comp->entity = this;
			return *comp;
		}
		return *static_cast<T*>(nullptr);
	}

	template<typename T>
	inline T& GetComponent() const
	{
		auto ptr(compList[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template<typename T>
	inline bool hasComponent() const
	{
		return compBitset[GetComponentTypeID<T>()];
	}



	void update()
	{
		for (auto& comp : components)
		{
			comp->update();
		}

	}

	
};

#pragma once
#include "Types.h"
#include "Component.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;
		float mass = 100.0f;
		double k = 0.000865;
		float maxSpeed = 2.0f;
		float minSpeed = -2.0f;
		Point2D velocity = Point2D(0.0f, 0.0f);
		Point2D acceleration = Point2D(0.0f, 0.0f);
		Point2D dragForce2D = Point2D(0.0f, 0.0f);
		Point2D force2D = Point2D(0.0f, 0.0f);
		void Run();
		void update();
	};
}
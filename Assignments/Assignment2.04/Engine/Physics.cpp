#include "Entity.h"
#include "Physics.h"
#include "Timing.h"
#include <Windows.h>
namespace Engine
{
	void PhysicsComponent::Run()
	{
		float dt = entity->GetComponent<TimingComponent>().dt;
		acceleration = entity->drivingForce2D / mass;
		dragForce2D = Point2D(-k * velocity.x * std::abs(velocity.x), -k * velocity.y * std::abs(velocity.y));
		acceleration = (entity->drivingForce2D + dragForce2D) / mass;
		if (velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}
		else if (velocity.x < minSpeed)
		{
			velocity.x = minSpeed;
		}
		else
		{
			velocity = velocity + Point2D(acceleration.x * dt, acceleration.y * dt);
		}

		if (velocity.y > maxSpeed)
		{
			velocity.y = maxSpeed;
		}
		else if (velocity.y < minSpeed)
		{
			velocity.y = minSpeed;
		}
		else
		{
			velocity = velocity + Point2D(acceleration.x * dt, acceleration.y * dt);
		}

		entity->position += Point2D(velocity.x * dt, velocity.y * dt);
		if (entity->position.x > 500.0f)
		{
			entity->position.x = 500.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}
		else if (entity->position.x < -500.0f)
		{
			entity->position.x = -500.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}

		if (entity->position.y > 400.0f)
		{
			entity->position.y = 400.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}
		else if (entity->position.y < -500.0f)
		{
			entity->position.y = -500.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}

	}

	void PhysicsComponent::update()
	{
		PhysicsComponent::Run();
	}
}
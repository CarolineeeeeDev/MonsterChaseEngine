#include "Physics.h"
#include <Windows.h>
namespace Engine
{
	void PhysicsComponent::Run(float dt, Player* player)
	{
		acceleration = player->drivingForce2D / mass;
		
		dragForce2D = Point2D(-k * velocity.x * std::abs(velocity.x), -k * velocity.y * std::abs(velocity.y));
		acceleration = (player->drivingForce2D + dragForce2D) / mass;
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
		
		player->position += Point2D(velocity.x * dt, velocity.y * dt);
		if (player->position.x > 500.0f)
		{
			player->position.x = 500.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}
		else if (player->position.x < -500.0f)
		{
			player->position.x = -500.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}

		if (player->position.y > 400.0f)
		{
			player->position.y = 400.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}
		else if (player->position.y < -500.0f)
		{
			player->position.y = -500.0f;
			acceleration = Point2D(0.0f, 0.0f);
			velocity = Point2D(0.0f, 0.0f);
		}
		

	}
}
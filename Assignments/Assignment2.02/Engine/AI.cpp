#include "AI.h"

namespace Engine
{
	void AIComponent::Run(float dt, int numMonsters, Monster** monsters)
	{
        for (int i = 0; i < numMonsters; ++i) {
            Point2D newPosition = monsters[i]->position;
            Point2D moveVelocity = Point2D(0.0f, 0.0f);
            if (i % 2 == 0) //up and down
            {
                if (!upDownFlag)
                {
                    moveVelocity = Point2D(0, 0.01f);
                }
                else
                {
                    moveVelocity = Point2D(0, -0.01f);
                }
                if (newPosition.y <= -400.0f)
                {
                    upDownFlag = false;
                }
                if (newPosition.y >= 400.0f)
                {
                    upDownFlag = true;
                }
                newPosition += moveVelocity;
            }
            else // left and right
            {
                if (!leftRightFlag)
                {
                    moveVelocity = Point2D(0.01f, 0);
                }
                else
                {
                    moveVelocity = Point2D(-0.01f, 0);
                }
                if (newPosition.x <= -400.0f)
                {
                    leftRightFlag = false;
                }
                if (newPosition.x >= 400.0f)
                {
                    leftRightFlag = true;
                }
                newPosition += moveVelocity;
            }

            monsters[i]->position = newPosition;

        }
	}
}
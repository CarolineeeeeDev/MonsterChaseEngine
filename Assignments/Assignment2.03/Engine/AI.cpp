#include "AI.h"
#include "Entity.h"
namespace Engine
{
    void AIComponent::Run()
    {
        Point2D newPosition = entity->position;
        Point2D moveVelocity = Point2D(0.0f, 0.0f);
        if (entity->id % 2 == 0) //up and down
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

        entity->position = newPosition;
    }
    void AIComponent::update()
    {
        AIComponent::Run();
    }
}
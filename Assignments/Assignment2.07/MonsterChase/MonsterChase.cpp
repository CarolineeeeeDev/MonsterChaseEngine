#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <DirectXColors.h>

#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>
#include <cmath>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "PlayerController.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectFactory.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

#include "GLib.h"
#include "MonsterChase.h"

namespace GLib
{

    void ConsolePrint(const char* i_pFmt, const char* i_pFile, unsigned int i_Line, ...);

} // namespace GLib

// This is how we handle variable argument pre-processor macros
// This is only supported by compilers that support the C99 standard
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT(fmt,...) GLib::ConsolePrint((fmt),__FILE__,__LINE__,__VA_ARGS__)
#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define DEBUG_PRINT(fmt,...) void(0)
#endif

namespace Engine {
    namespace Math {
        constexpr float Pi = 3.14159265358979323846f;

        inline float DegreesToRadians(float degrees) {
            return degrees * (Pi / 180.0f);
        }
    }
}


void SingleCollisionCheck();
void CollisionPoolCheck();




struct AABB
{
    Engine::Math::Vector3 m_Center;
    Engine::Math::Vector3 m_Extents;
};

struct Object
{
    Engine::Math::Vector3 m_Position;
    Engine::Math::Vector3 m_Velocity;
    Engine::Math::Matrix4 m_Orientation;

    AABB m_BB;
};

struct CollisionPair
{
    Object* m_pObjects[2];
    float m_CollisionTime;
};

bool CheckCollision(const Object& i_Obj1, const Object& i_Obj2, float i_dt, float& o_tCollision);

void SingleCollisionCheck()
{
    using namespace Engine::Math;

    Matrix4 mRot = Matrix4::CreateRotationZ(DegreesToRadians(90.0f));
    Matrix4 mTrans = Matrix4::CreateTranslation(0.0f, 100.0f, 0.0f);
    Matrix4 mToWorld = mTrans * mRot;

    Vector4 VXAxis(Vector3(1.0f, 0.0f, 0.0f), 1.0f);

    Vector4 VWorld = mToWorld * VXAxis;
    Matrix4 mFromWorld = mToWorld.GetInverse();
    Vector4 VBack = mFromWorld * VWorld;

    Object Obj1;
    Obj1.m_Position = Vector3(-1.0f, 0.0f, 0.0f);
    Obj1.m_Velocity = Vector3(1.0f, 0.0f, 0.0f);
    Obj1.m_Orientation = Matrix4::CreateRotationZ(DegreesToRadians(45.0f));
    Obj1.m_BB.m_Center = Vector3(0.0f, 0.0f, 0.0f);
    Obj1.m_BB.m_Extents = Vector3(0.5f, 0.5f, 0.5f);

    Object Obj2;
    Obj2.m_Position = Vector3(1.0f, 0.0f, 0.0f);
    Obj2.m_Velocity = Vector3(-1.0f, 0.0f, 0.0f);
    Obj2.m_Orientation = Matrix4::CreateRotationX(DegreesToRadians(45.0f));
    Obj2.m_BB.m_Center = Vector3(0.0f, 0.0f, 0.0f);
    Obj2.m_BB.m_Extents = Vector3(0.5f, 0.5f, 0.5f);

    float tCollision;
    bool bCollided = CheckCollision(Obj1, Obj2, 1.0f, tCollision);
    printf("Collided: %s\n", bCollided ? "true" : "false");
}

std::vector<Object*> m_CollisionObjects;

float RandInRange(float i_Min, float i_Max);
Engine::Math::Vector3 GenerateRandomVector(const Engine::Math::Vector3& i_Min, const Engine::Math::Vector3& i_Max);

CollisionPair FindCollision(float i_dt);

void CollisionPoolCheck()
{
    using namespace Engine::Math;

    const float AreaExtent = 10.0f;
    Vector3 PositionMin(-AreaExtent, -AreaExtent, -AreaExtent);
    Vector3 PositionMax(AreaExtent, AreaExtent, AreaExtent);

    Vector3 VelocityMin(-1.0f, -1.0f, -1.0f);
    Vector3 VelocityMax(1.0f, 1.0f, 1.0f);

    const size_t numObjects = 100;

    for (size_t i = 0; i < numObjects; i++)
    {
        Object* pObj = new Object;

        pObj->m_Position = GenerateRandomVector(PositionMin, PositionMax);
        pObj->m_Velocity = GenerateRandomVector(VelocityMin, VelocityMax);

        // Set random orientation
        float angle = RandInRange(0.0f, 360.0f);
        pObj->m_Orientation = Matrix4::CreateRotationZ(DegreesToRadians(angle));
        pObj->m_BB.m_Center = Vector3(0.0f, 0.0f, 0.0f);
        pObj->m_BB.m_Extents = Vector3(0.5f, 0.5f, 0.5f);

        m_CollisionObjects.push_back(pObj);
    }

    // Keep running to find collisions
    while (true)
    {
        CollisionPair Pair = FindCollision(RandInRange(0.1f, 1.0f));
    }
}

CollisionPair FindCollision(float i_dt)
{
    CollisionPair CurrentCollision = { { nullptr, nullptr }, 0.0f };

    const size_t count = m_CollisionObjects.size();

    for (size_t i = 0; i < (count - 1); i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            assert(m_CollisionObjects[i]);
            assert(m_CollisionObjects[j]);

            float tCollision = 0.0f;

            if (CheckCollision(*m_CollisionObjects[i], *m_CollisionObjects[j], i_dt, tCollision))
            {
                if (CurrentCollision.m_pObjects[0])
                {
                    if (tCollision < CurrentCollision.m_CollisionTime)
                    {
                        CurrentCollision.m_pObjects[0] = m_CollisionObjects[i];
                        CurrentCollision.m_pObjects[1] = m_CollisionObjects[j];
                        CurrentCollision.m_CollisionTime = tCollision;
                    }
                }
                else
                {
                    CurrentCollision.m_pObjects[0] = m_CollisionObjects[i];
                    CurrentCollision.m_pObjects[1] = m_CollisionObjects[j];
                    CurrentCollision.m_CollisionTime = tCollision;
                }
            }
        }
    }
    return CurrentCollision;
}

float RandInRange(float i_Min, float i_Max)
{
    return i_Min + (static_cast<float>(rand()) / (RAND_MAX + 1) * (i_Max - i_Min + 1.0f));
}

Engine::Math::Vector3 GenerateRandomVector(const Engine::Math::Vector3& i_Min, const Engine::Math::Vector3& i_Max)
{
    return Engine::Math::Vector3(
        RandInRange(i_Min.x(), i_Max.x()),
        RandInRange(i_Min.y(), i_Max.y()),
        RandInRange(i_Min.z(), i_Max.z())
    );
}

bool IsZero(float i_value);

bool CheckCollision(const Object& i_Obj1, const Object& i_Obj2, float i_dt, float& o_tCollision)
{
    using namespace Engine::Math;

    Matrix4 Obj1ToWorld = Matrix4::CreateTranslation(i_Obj1.m_Position.x(), i_Obj1.m_Position.y(), i_Obj1.m_Position.z()) * Matrix4(i_Obj1.m_Orientation);

    Matrix4 Obj2ToWorld = Matrix4::CreateTranslation(i_Obj2.m_Position.x(), i_Obj2.m_Position.y(), i_Obj2.m_Position.z()) * Matrix4(i_Obj2.m_Orientation);


    Vector4 Obj1BBCenterInWorld = Obj1ToWorld * i_Obj1.m_BB.m_Center;
    Vector4 Obj2BBCenterInWorld = Obj2ToWorld * i_Obj2.m_BB.m_Center;

    float tEnter = 0.0f;
    float tExit = 1.0f;

    float axisEnter = 0.0f;
    float axisExit = 1.0f;

    Vector3 CollisionAxis;

    CollisionAxis = i_Obj1.m_Orientation.Row(0).xyz().Normalized();

    bool CheckSeparationAlongAxis(const Engine::Math::Vector3 i_CollisionAxis, const Object & i_Obj1, const Engine::Math::Vector3 i_Obj1BBCenterInWorld,
        const Object & i_Obj2, const Engine::Math::Vector3 i_Obj2BBCenterInWorld, float i_dt,
        float i_tEnter, float i_tExit);

    if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
    {
        DEBUG_PRINT("Found Separation along Obj1 X Axis");
        return false;
    }
    else
    {
        DEBUG_PRINT("Found Overlap along Obj1 X Axis from %f to %f", axisEnter, axisExit);
        if (axisEnter > tEnter)
        {
            DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
            tEnter = axisEnter;
        }
        if (axisExit < tExit)
        {
            DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
            tExit = axisExit;
        }
    }

    CollisionAxis = i_Obj1.m_Orientation.Row(1).xyz().Normalized();
    if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
    {
        DEBUG_PRINT("Found Separation along Obj1 Y Axis");
        return false;
    }
    else
    {
        DEBUG_PRINT("Found Overlap along Obj1 Y Axis from %f to %f", axisEnter, axisExit);
        if (axisEnter > tEnter)
        {
            DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
            tEnter = axisEnter;
        }
        if (axisExit < tExit)
        {
            DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
            tExit = axisExit;
        }
    }

    CollisionAxis = i_Obj1.m_Orientation.Row(2).xyz().Normalized();
    if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
    {
        DEBUG_PRINT("Found Separation along Obj1 Z Axis");
        return false;
    }
    else
    {
        DEBUG_PRINT("Found Overlap along Obj1 Z Axis from %f to %f", axisEnter, axisExit);
        if (axisEnter > tEnter)
        {
            DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
            tEnter = axisEnter;
        }
        if (axisExit < tExit)
        {
            DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
            tExit = axisExit;
        }
    }

    CollisionAxis = i_Obj2.m_Orientation.Row(0).xyz().Normalized();
    if (CheckSeparationAlongAxis(CollisionAxis, i_Obj2, Obj2BBCenterInWorld.xyz(), i_Obj1, Obj1BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
    {
        DEBUG_PRINT("Found Separation along Obj2 X Axis");
        return false;
    }
    else
    {
        DEBUG_PRINT("Found Overlap along Obj2 X Axis from %f to %f", axisEnter, axisExit);
        if (axisEnter > tEnter)
        {
            DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
            tEnter = axisEnter;
        }
        if (axisExit < tExit)
        {
            DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
            tExit = axisExit;
        }
    }

    CollisionAxis = i_Obj2.m_Orientation.Row(1).xyz().Normalized();
    if (CheckSeparationAlongAxis(CollisionAxis, i_Obj2, Obj2BBCenterInWorld.xyz(), i_Obj1, Obj1BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
    {
        DEBUG_PRINT("Found Separation along Obj2 Y Axis");
        return false;
    }
    else
    {
        DEBUG_PRINT("Found Overlap along Obj2 Y Axis from %f to %f", axisEnter, axisExit);
        if (axisEnter > tEnter)
        {
            DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
            tEnter = axisEnter;
        }
        if (axisExit < tExit)
        {
            DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
            tExit = axisExit;
        }
    }

    CollisionAxis = i_Obj2.m_Orientation.Row(2).xyz().Normalized();
    if (CheckSeparationAlongAxis(CollisionAxis, i_Obj2, Obj2BBCenterInWorld.xyz(), i_Obj1, Obj1BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
    {
        DEBUG_PRINT("Found Separation along Obj1 Z Axis");
        return false;
    }
    else
    {
        DEBUG_PRINT("Found Overlap along Obj1 Z Axis from %f to %f", axisEnter, axisExit);
        if (axisEnter > tEnter)
        {
            DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
            tEnter = axisEnter;
        }
        if (axisExit < tExit)
        {
            DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
            tExit = axisExit;
        }
    }

    

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(0).xyz(), i_Obj2.m_Orientation.Row(0).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 X x Obj2 X Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 X x Obj2 X Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(0).xyz(), i_Obj2.m_Orientation.Row(1).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 X x Obj2 Y Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 X x Obj2 Y Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(0).xyz(), i_Obj2.m_Orientation.Row(2).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 X x Obj2 Z Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 X x Obj2 Z Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(1).xyz(), i_Obj2.m_Orientation.Row(0).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 Y x Obj2 X Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 Y x Obj2 X Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(1).xyz(), i_Obj2.m_Orientation.Row(1).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 Y x Obj2 Y Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 Y x Obj2 Y Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(1).xyz(), i_Obj2.m_Orientation.Row(2).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 Y x Obj2 Z Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 Y x Obj2 Z Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(2).xyz(), i_Obj2.m_Orientation.Row(0).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 Z x Obj2 X Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 Z x Obj2 X Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(2).xyz(), i_Obj2.m_Orientation.Row(1).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 Z x Obj2 Y Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 Z x Obj2 Y Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    CollisionAxis = cross(i_Obj1.m_Orientation.Row(2).xyz(), i_Obj2.m_Orientation.Row(2).xyz());
    if (!IsZero(CollisionAxis.LengthSq()))
    {
        if (CheckSeparationAlongAxis(CollisionAxis, i_Obj1, Obj1BBCenterInWorld.xyz(), i_Obj2, Obj2BBCenterInWorld.xyz(), i_dt, axisEnter, axisExit))
        {
            DEBUG_PRINT("Found Separation along Obj1 Z x Obj2 Z Axis");
            return false;
        }
        else
        {
            DEBUG_PRINT("Found Overlap along Obj1 Z x Obj2 Z Axis from %f to %f", axisEnter, axisExit);
            if (axisEnter > tEnter)
            {
                DEBUG_PRINT("Updating tEnter to %f\n", axisEnter);
                tEnter = axisEnter;
            }
            if (axisExit < tExit)
            {
                DEBUG_PRINT("Updating tExit to %f\n", axisEnter);
                tExit = axisExit;
            }
        }
    }

    if (tEnter < tExit)
    {
        o_tCollision = tEnter;
        return true;
    }
    else
        return false;
}

bool DetectCrossTimes(float i_Center, float i_Extent, float i_Point, float i_Travel, float& o_tEnter, float& o_tExit);

bool CheckSeparationAlongAxis(const Engine::Math::Vector3 i_CollisionAxis, const Object& i_Obj1, const Engine::Math::Vector3 i_Obj1BBCenterInWorld,
    const Object& i_Obj2, const Engine::Math::Vector3 i_Obj2BBCenterInWorld, float i_dt,
    float i_tEnter, float i_tExit)
{
    using namespace Engine::Math;

    float Obj1BBCenterOnAxis = dot(i_Obj1BBCenterInWorld, i_CollisionAxis);
    float Obj2BBCenterOnAxis = dot(i_Obj2BBCenterInWorld, i_CollisionAxis);

    float Obj1ProjectedExtents = fabs(dot(i_CollisionAxis, i_Obj1.m_Orientation.Row(0).xyz().Normalized() * i_Obj1.m_BB.m_Extents.x())) +
        fabs(dot(i_CollisionAxis, i_Obj1.m_Orientation.Row(1).xyz().Normalized() * i_Obj1.m_BB.m_Extents.y())) +
        fabs(dot(i_CollisionAxis, i_Obj1.m_Orientation.Row(2).xyz().Normalized() * i_Obj1.m_BB.m_Extents.z()));

    float Obj2ProjectedExtents = fabs(dot(i_CollisionAxis, i_Obj2.m_Orientation.Row(0).xyz().Normalized() * i_Obj2.m_BB.m_Extents.x())) +
        fabs(dot(i_CollisionAxis, i_Obj2.m_Orientation.Row(1).xyz().Normalized() * i_Obj2.m_BB.m_Extents.y())) +
        fabs(dot(i_CollisionAxis, i_Obj2.m_Orientation.Row(2).xyz().Normalized() * i_Obj2.m_BB.m_Extents.z()));

    float Obj2ExpandedExtents = Obj2ProjectedExtents + Obj1ProjectedExtents;

    float Obj1VelOnAxis = dot(i_Obj1.m_Velocity, i_CollisionAxis);
    float Obj2VelOnAxis = dot(i_Obj2.m_Velocity, i_CollisionAxis);

    float Obj1RelVel = Obj1VelOnAxis - Obj2VelOnAxis;

    float Obj1TravelAlongAxis = Obj1RelVel * i_dt;

    i_tEnter = 0.0f;
    i_tExit = 1.0f;

    return !DetectCrossTimes(Obj2BBCenterOnAxis, Obj2ExpandedExtents, Obj1BBCenterOnAxis, Obj1TravelAlongAxis, i_tEnter, i_tExit);
}


inline void Swap(float& i_a, float& i_b);
bool DetectCrossTimes(float i_Center, float i_Extent, float i_Point, float i_Travel, float& o_tEnter, float& o_tExit)
{
    assert(i_Extent > 0.0f);

    using namespace Engine::Math;


    float i_Start = i_Center - i_Extent;
    float i_End = i_Center + i_Extent;


    if (IsZero(i_Travel))
    {
        if ((i_Point < i_Start) || (i_Point > i_End))
            return false;
        else
        {
            o_tEnter = 0.0f;
            o_tExit = 1.0f;
            return true;
        }
    }

    o_tEnter = (i_Start - i_Point) / i_Travel;
    o_tExit = (i_End - i_Point) / i_Travel;


    if (o_tEnter > o_tExit)
        Swap(o_tEnter, o_tExit);

    return !(o_tEnter >= 1.0f || o_tExit <= 0.0f);
}

inline bool IsZero(float i_value)
{
    return fabs(i_value) < 1e-5;
}

inline void Swap(float& i_a, float& i_b)
{
    float temp = i_a;
    i_a = i_b;
    i_b = temp;
}


void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG


	UpdatePlayerPos(i_VKeyID, bWentDown);

}

void UpdatePlayerPos(unsigned int i_VKeyID, bool bWentDown)
{
	if (bWentDown == true)
	{
		if (i_VKeyID == 0x51) //Q
		{
			exit(0);
		}
		else {
			if (!isGameOver)
			{
				if (i_VKeyID == 0x57) {//W
					manager->entities[0]->drivingForce2D = Engine::Point2D(0, 2.0f);
				}
				else if (i_VKeyID == 0x53) {//S
					manager->entities[0]->drivingForce2D = Engine::Point2D(0, -2.0f);
				}
				else if (i_VKeyID == 0x41) {//A
					manager->entities[0]->drivingForce2D = Engine::Point2D(-2.0f, 0);
				}
				else if (i_VKeyID == 0x44) {//D
					manager->entities[0]->drivingForce2D = Engine::Point2D(2.0f, 0);
				}
			}


		}

	}
}

void InitiatePlayerEntity()
{

	std::shared_ptr<Entity> playerEntity = std::make_shared<Entity>();
	playerEntity->id = 0;
	playerEntity->sprite = CreateSprite("data\\Player.dds");
	playerEntity->position = Engine::Point2D(-500.0f, -500.0f);
	playerEntity->AddComponent<Engine::TimingComponent>();
	playerEntity->AddComponent<Engine::PhysicsComponent>();
	playerEntity->AddComponent<Engine::RendererComponent>();
	manager->addEntity(playerEntity);
}
void InitiateMonsterEntity(int numMonsters)
{
	default_random_engine e(static_cast<unsigned int> (time(0)));
	for (int i = 0; i < numMonsters; i++)
	{

		std::shared_ptr<Entity> monsterEntity = std::make_shared<Entity>();
		monsterEntity->id = i + 1;
		monsterEntity->position = Engine::Point2D(-(float)(e() % 500), -(float)(e() % 500));
		monsterEntity->sprite = CreateSprite("data\\Monster.dds");
		monsterEntity->AddComponent<Engine::AIComponent>();
		monsterEntity->AddComponent<Engine::RendererComponent>();
		manager->addEntity(monsterEntity);
	}
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	isGameOver = false;
	numMonsters = 4;
	manager = std::make_shared<EntityManager>();

	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 1200, true);

	if (bSuccess)
	{
		using namespace Engine;

		GameObjectFactory::RegisterControllerCreator("player", &PlayerController::Create);
		std::shared_ptr<GameObject> pNewGameObject(GameObjectFactory::CreateGameObject("data\\Player.json"));
		InitiatePlayerEntity();
		InitiateMonsterEntity(numMonsters);

		bQuit = false;
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		while (bQuit == false)
		{
			manager->update(bQuit,isGameOver, manager);
		} 
		

		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}





GLib::Sprite* CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return nullptr;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(*pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::SpriteEdges	Edges = { -float(width / 8.0f), float(height / 2.0f), float(width / 4.0f), 0.0f };
	GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

	// release our reference on the Texture
	GLib::Release(pTexture);

	return pSprite;
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

#pragma once
#include <array>
#include <bitset>
#include <vector>


class Entity;
class Component;

using ComponentTypeID = size_t;

inline ComponentTypeID GetUniqueComponentID()
{
	static ComponentTypeID lastID = 0u;
	return lastID++;
}

template<typename T>
inline ComponentTypeID GetComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "Type not based on component!");
	static const ComponentTypeID typeID = GetUniqueComponentID();
	return typeID;
}

constexpr size_t MAX_ENTITIES = 5000;
constexpr size_t MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentList = std::array<Component*, MAX_COMPONENTS>;

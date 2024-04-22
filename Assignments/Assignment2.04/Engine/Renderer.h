#pragma once
#include "GLib.h"
#include "Types.h"
#include <vector>
#include "Component.h"
#include "EntityManager.h"

namespace Engine
{
	class RendererComponent : public Component
	{
	public:
		RendererComponent() = default;
		void Draw(bool bQuit);
		void update(bool bQuit, EntityManager* manager);
	};
}
#pragma once

#include "GameObject.h"

#include "nlohmann/json.hpp"

namespace Engine
{
	namespace GameObjectFactory
	{
		GameObject* CreateGameObject(const char* i_pJSONConfig);

		void RegisterControllerCreator(const std::string& i_ControllerName, std::function<void(GameObject&, nlohmann::json&)> i_ControllerCreator);
		void RegisterComponentCreator(const std::string& i_ControllerName, std::function<void(GameObject&, nlohmann::json&)> i_ComponentCreator);
	}
}
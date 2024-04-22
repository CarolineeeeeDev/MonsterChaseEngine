#pragma once

#include "Component.h"
#include "GameObject/GameObjectController.h"
#include <memory>
#include <functional>
#include <map>
#include <string>

namespace Engine
{
	class GameObject
	{
	public:
		std::shared_ptr<IComponent> EnsureComponent(const char* i_ComponentName, std::function<IComponent*(void)> i_Creator)
		{
			auto ComponentIterator = Components.find(i_ComponentName);

			if (ComponentIterator != Components.end())
				return ComponentIterator->second;

			std::shared_ptr<IComponent> pNewComponent = std::shared_ptr<IComponent>(i_Creator());

			Components.emplace(std::make_pair(i_ComponentName, pNewComponent));
			return pNewComponent;
		}

		void Update()
		{
			if (pController)
				pController->Update(*this);
		}

		void SetCurrentController(std::shared_ptr<IGameObjectController> pNewController) { pController = pNewController; }

	private:
		std::shared_ptr<IGameObjectController> pController;
		std::map<std::string /*component_name*/, std::shared_ptr<IComponent> /*component*/> Components;
	};
}
#pragma once

#include "Component.h"
#include "GameObject/GameObjectController.h"

#include <functional>
#include <map>
#include <string>

namespace Engine
{
	class GameObject
	{
	public:
		IComponent* EnsureComponent(const char* i_ComponentName, std::function<IComponent*(void)> i_Creator)
		{
			auto ComponentIterator = Components.find(i_ComponentName);

			if (ComponentIterator != Components.end())
				return ComponentIterator->second;

			IComponent* pNewComponent = i_Creator();

			Components.emplace(std::make_pair(i_ComponentName, pNewComponent));
			return pNewComponent;
		}

		void Update()
		{
			if (pController)
				pController->Update(*this);
		}

		void SetCurrentController(IGameObjectController* pNewController) { pController = pNewController; }

	private:
		IGameObjectController* pController;
		std::map<std::string /*component_name*/, IComponent* /*component*/> Components;
	};
}
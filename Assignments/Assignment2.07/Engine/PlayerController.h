#pragma once

#include "GameObject/Component.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectController.h"
#include "GameObject/Vector3Component.h"

#include "GLib.h"

#include "nlohmann/json.hpp"

#include <functional>
#include <iostream>

class PlayerController : public Engine::IGameObjectController
{
public:
	PlayerController()
	{
		// this is an example of binding a class instance and method to a std::function.
		// We bind PlayerController::KeypressHandler and this instance.
		// std::placeholder is needed with std::bind if we're not bindind the parameters that the function needs at this time
		// they'll be bound at the call time.
		GLib::SetKeyStateChangeCallback(std::bind(&PlayerController::KeypressHandler,this,std::placeholders::_1, std::placeholders::_2));
	}

	virtual void Update(Engine::GameObject& Object) override
	{
		// Do something here
	}

	static void Create(Engine::GameObject& NewGameObject, nlohmann::json& InitializerSection)
	{
		assert(InitializerSection["name"].is_string());

		std::string PlayerName = InitializerSection["name"];

		PlayerController* pNewPlayerController = new PlayerController();

		// this is an example of a lambda with capture. The PlayerName string is passed into the captured function.
		NewGameObject.EnsureComponent("Name", [PlayerName]()
			{
				return new Engine::StringComponent("Name", PlayerName.c_str());
			});

		// Ensure we have a force component. This is what we'll manipulate based on keypresses.
		NewGameObject.EnsureComponent("Force", []()
			{
				return new Engine::Vector3Component("Force");
			});
	}
private:

	void KeypressHandler(unsigned int i_VKeyID, bool i_bDown)
	{
		// Do something here
	}

};


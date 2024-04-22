#include "GameObjectFactory.h"

#include "GameObject.h"
#include "File/LoadFileToBuffer.h"
#include "Math/Vector3.h"

#include <functional>
#include <map>
#include <string>

#include "nlohmann/json.hpp"

namespace Engine
{
	namespace GameObjectFactory
	{
		// we could probably genericize the following down to something like
		// std::map<std::string, std::map<std::string, std::function<void(GameObject&, nlohmann::json&)> > > FlexibleSectionHandles;

		std::map<std::string, std::function<void(GameObject&, nlohmann::json&)> > ControllerCreators;
		std::map<std::string, std::function<void(GameObject&, nlohmann::json&)> > ComponentCreators;

		std::shared_ptr<GameObject> CreateGameObject(nlohmann::json& ConfigData)
		{
			using json = nlohmann::json;

			std::shared_ptr<GameObject> NewGameObject = std::make_shared<GameObject>();

			if (ConfigData.contains("controller"))
			{
				assert(ConfigData["controller"].is_object());
				assert(ConfigData["controller"]["type"].is_string());
				assert(ConfigData["controller"]["initializer"].is_object());


				auto ControllerCreator = ControllerCreators.find(ConfigData["controller"]["type"]);
				if (ControllerCreator != ControllerCreators.end())
				{
					ControllerCreator->second(*NewGameObject, ConfigData["controller"]["initializer"]);
				}
			}

			if (ConfigData.contains("components"))
			{
				assert(ConfigData["components"].is_object());

				for (json::iterator it = ConfigData["components"].begin(); it != ConfigData["components"].end(); ++it)
				{
					const std::string& ComponentName = it.key();

					auto ComponentCreator = ComponentCreators.find(ComponentName);
					if (ComponentCreator != ComponentCreators.end())
					{
						ComponentCreator->second(*NewGameObject, it.value());
					}
				}
			}

			return NewGameObject;
		}

		std::shared_ptr<GameObject> CreateGameObject(const char* i_pJSONConfig)
		{
			using namespace Engine;
			using json = nlohmann::json;

			std::vector<uint8_t> ConfigDataData = LoadFileToBuffer(i_pJSONConfig);

			if (!ConfigDataData.empty())
			{
				json ConfigDataJSON = json::parse(ConfigDataData);
				return CreateGameObject(ConfigDataJSON);
			}
			else
			{
				return nullptr;
			}
		}

		void RegisterControllerCreator(const std::string& i_ControllerName, std::function<void(GameObject&, nlohmann::json&)> i_ControllerCreator)
		{
			ControllerCreators.insert({ i_ControllerName, i_ControllerCreator });
		}

		void RegisterComponentCreator(const std::string& i_ComponentName, std::function<void(GameObject&, nlohmann::json&)> i_ComponentCreator)
		{
			ComponentCreators.insert({ i_ComponentName, i_ComponentCreator });
		}
	}
}

#pragma once

namespace Engine
{
	// forward declare the GameObject class
	class GameObject;

	class IGameObjectController
	{
	public:
		virtual void Update(GameObject& i_GameObject) = 0;
	};

}



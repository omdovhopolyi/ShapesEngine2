#pragma once

//#include "ECS/SystemsManager.h"
//#include "Resources/ResourcesManager.h"
#include "Messenger/SubscriptionsContainer.h"
#include <memory>

namespace shen
{
	class SystemsManager;
	class ResourcesManager;

	class Game
	{
	public:
		Game();
		~Game();

		void Initialize();
		void Run();
		void Destroy();

	private:
		void Setup();
		void Update();

	private:
		int _lastUpdateTime = 0;
		bool _isRunning = false;
		SubcriptionsContainer _subscriptions;
		std::unique_ptr<SystemsManager> _systems;
		std::unique_ptr<ResourcesManager> _resources;
	};
}

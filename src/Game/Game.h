#pragma once

#include "Messenger/SubscriptionsContainer.h"
#include "ECS/SystemsListLoader.h"
#include <memory>

namespace shen
{
	class SystemsManager;

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
		SystemsListLoader _systemsLoader;
	};
}

#pragma once

#include "ECS/SystemsManager.h"
#include "Resources/ResourcesManager.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
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
		SystemsManager _systems;
		ResourcesManager _resources;
	};
}

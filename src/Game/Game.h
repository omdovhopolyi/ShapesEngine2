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

		bool IsRunning() const;

	private:
		void InitSubscriptions();
		bool CreateSystems();
		void LoadSystems();
		void InitSystems();
		void SetupSystems();
		void Update();

		void SetRunning(bool running);

	private:
		int _lastUpdateTime = 0;
		bool _isRunning = false;
		SubcriptionsContainer _subscriptions;
		std::unique_ptr<SystemsManager> _systems;
		SystemsListLoader _systemsLoader;
	};
}

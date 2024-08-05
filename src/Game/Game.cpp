#include "Game.h"
#include "ECS/SystemsManager.h"
#include "ECS/SystemsFactory.h"
#include "Logger/Logger.h"
#include "Messenger/Events/Common.h"

namespace shen
{
	Game::Game() = default;
	Game::~Game() = default;

	void Game::Initialize()
	{
		const bool loaded = _systemsLoader.Load();
		if (loaded)
		{
			_systems = std::make_unique<SystemsManager>();
			_systems->Init(this);

			for (const auto& systemType : _systemsLoader.GetSystemsList())
			{
				_systems->AddSystem(SystemsFactory::Instance().Get(systemType));
			}

			_isRunning = true;
		}
	}

	void Game::Run()
	{
		Setup();

		while (_isRunning)
		{
			Update();
		}
	}

	void Game::Destroy()
	{
		_systems->Clear();
	}

	void Game::Setup()
	{
		if (_isRunning)
		{
			_systems->Start();
		}

		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			_isRunning = false;
		});
	}

	void Game::Update()
	{
		_systems->Update();
		_systems->Draw();
	}
}

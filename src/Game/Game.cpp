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
		InitSubscriptions();
		const bool loaded = CreateSystems();
		SetRunning(loaded);

		if (IsRunning())
		{
			LoadSystems();
			InitSystems();
			SetupSystems();
		}
	}

	void Game::Run()
	{
		while (_isRunning)
		{
			Update();
		}
	}

	void Game::Destroy()
	{
		_systems->Clear();
	}

	bool Game::IsRunning() const
	{
		return _isRunning;
	}

	void Game::InitSubscriptions()
	{
		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			SetRunning(false);
		});
	}

	bool Game::CreateSystems()
	{
		const bool loaded = _systemsLoader.Load();
		if (loaded)
		{
			_systems = std::make_unique<SystemsManager>();

			for (const auto& systemType : _systemsLoader.GetSystemsList())
			{
				_systems->AddSystem(SystemsFactory::Instance().Get(systemType));
			}
		}

		return loaded;
	}

	void Game::LoadSystems()
	{
		_systems->Load();
	}

	void Game::InitSystems()
	{
		_systems->Init(this);
	}

	void Game::SetupSystems()
	{
		_systems->Start();
	}

	void Game::Update()
	{
		_systems->Update();
		_systems->Draw();
	}

	void Game::SetRunning(bool running)
	{
		_isRunning = running;
	}
}

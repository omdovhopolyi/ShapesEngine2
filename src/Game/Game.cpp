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
		const bool loaded = LoadSystems();
		_isRunning = loaded;
	}

	void Game::Run()
	{
		PreStart();
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

	void Game::InitSubscriptions()
	{
		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			_isRunning = false;
		});
	}

	bool Game::LoadSystems()
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

			return true;
		}

		return false;
	}

	void Game::PreStart()
	{
		if (_isRunning)
		{
			_systems->Load();
		}
	}

	void Game::Setup()
	{
		if (_isRunning)
		{
			_systems->Start();
		}

		
	}

	void Game::Update()
	{
		_systems->Update();
		_systems->Draw();
	}
}

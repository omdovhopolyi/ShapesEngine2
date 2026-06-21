#include "Engine.h"
#include "ECS/SystemsManager.h"
#include "ECS/SystemsFactory.h"
#include "Logger/Logger.h"
#include "Messenger/Events/Common.h"

namespace shen
{
	Engine::Engine() = default;
	Engine::~Engine() = default;

	void Engine::Initialize()
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

	void Engine::Run()
	{
		while (_isRunning)
		{
			Update();
		}
	}

	void Engine::Destroy()
	{
		_systems->Clear();
	}

	bool Engine::IsRunning() const
	{
		return _isRunning;
	}

	void Engine::InitSubscriptions()
	{
		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			SetRunning(false);
		});
	}

	bool Engine::CreateSystems()
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

	void Engine::LoadSystems()
	{
		_systems->Load();
	}

	void Engine::InitSystems()
	{
		_systems->Init(this);
	}

	void Engine::SetupSystems()
	{
		_systems->Start();
	}

	void Engine::Update()
	{
		_systems->Update();
		_systems->Draw();
	}

	void Engine::SetRunning(bool running)
	{
		_isRunning = running;
	}
}

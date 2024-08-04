#include "Game.h"
#include "ECS/SystemsManager.h"
#include "Logger/Logger.h"
#include "Time.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "Messenger/Events/Common.h"
#include "ECS/Systems/InputCommandsCollection.h"
#include "ECS/Systems/WorldInputSystem.h"
#include "ECS/Systems/UIInputSystem.h"
#include "ECS/Systems/PlayerInputSystem.h"
#include "ECS/Systems/CameraSystem.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/RotationSystem.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "ECS/Systems/SpriteFrameAnimationSystem.h"
#include "ECS/Systems/WindowsManager.h"
#include "ECS/Systems/WindowsRenderSystem.h"
#include "ECS/Systems/Sfml/SfmlInputSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/Systems/Sfml/SfmlSpriteRenderSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowBeginFrameSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowEndFrameSystem.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "ECS/Systems/Sfml/SfmlFontsCollection.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/SystemsFactory.h"

#include <sstream>
#include <fstream>

namespace shen
{
	Game::Game()
	{
		Logger::Log("Game constructor");
	}

	Game::~Game()
	{
		Logger::Log("Game destructor");
	}

	void Game::Initialize()
	{
		_systems = std::make_unique<SystemsManager>();

		_systems->Init(this);

		_systems->AddSystem(SystemsFactory::Instance().Get("WindowsManager"));

		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlTexturesCollection"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlFontsCollection"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlSpritesCollection"));
		_systems->AddSystem(SystemsFactory::Instance().Get("InputCommandsCollection"));
		_systems->AddSystem(SystemsFactory::Instance().Get("MapLoaderSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlGameWindowSystem"));

		_systems->AddSystem(SystemsFactory::Instance().Get("TimeSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlInputSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("PlayerInputSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("WorldInputSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("UIInputSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("CameraSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("MovementSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("RotationSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("PhysicsBox2DSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SpriteFrameAnimationSystem"));

		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlWindowBeginFrameSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlSpriteRenderSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("WindowsRenderSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlRenderTargetsSystem"));
		_systems->AddSystem(SystemsFactory::Instance().Get("SfmlWindowEndFrameSystem"));

		_isRunning = true;
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
		_systems->Start();

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

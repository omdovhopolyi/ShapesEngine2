#include "Game.h"
#include "ECS/SystemsManager.h"
#include "Logger/Logger.h"
#include "Time.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "Messenger/Events/Common.h"
#include "ECS/Systems/InputCommandsCollection.h"
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
		_systems->RegisterSystem<WindowsManager>();
		_systems->RegisterSystem<SfmlTexturesCollection>();
		_systems->RegisterSystem<InputCommandsCollection>();
		_systems->RegisterSystem<MapLoaderSystem>();
		_systems->RegisterSystem<SfmlGameWindowSystem>();

		_systems->RegisterSystem<TimeSystem>();
		_systems->RegisterSystem<SfmlInputSystem>();
		_systems->RegisterSystem<PlayerInputSystem>();
		_systems->RegisterSystem<CameraSystem>();
		_systems->RegisterSystem<MovementSystem>();
		_systems->RegisterSystem<RotationSystem>();
		_systems->RegisterSystem<PhysicsBox2DSystem>();
		_systems->RegisterSystem<SpriteFrameAnimationSystem>();

		_systems->RegisterSystem<SfmlWindowBeginFrameSystem>();
		_systems->RegisterSystem<SfmlSpriteRenderSystem>();
		_systems->RegisterSystem<WindowsRenderSystem>();
		_systems->RegisterSystem<SfmlWindowEndFrameSystem>();

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

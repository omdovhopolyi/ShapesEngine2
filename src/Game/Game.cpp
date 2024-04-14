
#include "Game.h"
#include "ManagersProvider.h"
#include "Logger/Logger.h"
#include "Time.h"
#include "GameWindow.h"
#include "MapLoader.h"

#include "ECS/SystemsManager.h"


#include "ECS/Components/Common.h"


#include "Resources/AssetsManager.h"

#include "Resources/ShadersManager.h"

#include "Messenger/Events/Common.h"

#include "ECS/Systems/TimeSystem.h"
#include "ECS/Systems/Sfml/SfmlInputSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"

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
		_systems.Init(this);
		_systems.RegisterSystem<TimeSystem>();
		_systems.RegisterSystem<SfmlInputSyste>();
		_systems.RegisterSystem<SfmlGameWindowSystem>();

		/*_systems->RegisterSystem<SDLInputSystem>();
		_systems->RegisterSystem<CameraSystem>();
		_systems->RegisterSystem<SpriteFrameAnimationSystem>();
		_systems->RegisterSystem<PlayerInputSystem>();
		_systems->RegisterSystem<PhysicsBox2DSystem>();
		_systems->RegisterSystem<MovementSystem>();
		_systems->RegisterSystem<RotationSystem>();
		_systems->RegisterSystem<IntertiaSystem>();

		_systems->RegisterRenderSystem<OpenGLGridRenderSystem>();
		_systems->RegisterRenderSystem<OpenGLSpriteRenderSystem>();*/
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
		_systems.Clear();
		_resources.Clear();
	}

	void Game::Setup()
	{
		_systems.Start();

		//RegisterSystems();

		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			_isRunning = false;
		});

		/*auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<OpenGLTexturesManager>();

		auto mapLoader = ManagersProvider::Instance().GetMapLoader();
		mapLoader->LoadMap("map_test");*/
	}

	void Game::Update()
	{
		_systems.Update();
		_systems.Draw();
	}
}

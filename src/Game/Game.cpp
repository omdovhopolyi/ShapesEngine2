
#include "Game.h"
#include "ManagersProvider.h"
#include "Logger/Logger.h"
#include "Time.h"
#include "GameWindow.h"

#include "ECS/SystemsManager.h"
#include "ECS/EcsWorld.h"
#include "ECS/SystemsRegistration.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"

#include "Resources/AssetsManager.h"
#include "Resources/SDLTexturesManager.h"

#include "Messenger/Events/Common.h"

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
		_isRunning = ManagersProvider::Instance().Init();
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
		ManagersProvider::Instance().Clear();
	}

	void Game::Setup()
	{
		RegisterSystems();

		// TODO hard refactoring

		_subscriptions.Subscribe<KeyEvent>([this](const auto& event)
		{
			if (event.type == KeyEventType::Up)
			{
				if (event.code == SDLK_ESCAPE)
				{
					_isRunning = false;
				}
			}
		});

		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			_isRunning = false;
		});

		auto world = ManagersProvider::Instance().GetWorld();

		auto sdlTexturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();
		sdlTexturesManager->LoadAsset("tank", "../assets/images/tank-panther-right.png");
		sdlTexturesManager->LoadAsset("tilemap", "../assets/tilemaps/jungle.png");
		sdlTexturesManager->LoadAsset("chopper", "../assets/images/chopper-spritesheet.png");

		auto tank1 = world->CreateEntity();
		world->AddComponent<Transform>(tank1, glm::vec3(500.f, 10.f, 1.f), 0.f, glm::vec3(1.f, 1.f, 1.f));
		world->AddComponent<RigidBody>(tank1, glm::vec3(0.f, 0.f, 0.f));
		world->AddComponent<SDLSprite>(tank1, sdlTexturesManager->GetAsset("tank"), 32, 32, 0, 0, 32, 32);
		world->AddComponent<BoundingBox>(tank1, glm::vec3(32, 32, 0));

		auto tank2 = world->CreateEntity();
		world->AddComponent<Transform>(tank2, glm::vec3(500.f, 500.f, 1.f), 0.f, glm::vec3(1.f, 1.f, 1.f));
		world->AddComponent<RigidBody>(tank2, glm::vec3(0.f, 0.f, 0.f));
		world->AddComponent<SDLSprite>(tank2, sdlTexturesManager->GetAsset("tank"), 32, 32, 0, 0, 32, 32);
		world->AddComponent<BoundingBox>(tank2, glm::vec3(32, 32, 0));

		auto playerEntity = world->CreateEntity();
		world->AddComponent<PlayerInput>(playerEntity);
		world->AddComponent<CameraTarget>(playerEntity);
		world->AddComponent<RigidBody>(playerEntity);
		world->AddComponent<Transform>(playerEntity, glm::vec3(400.f, 320.f, 2.f), 0.f, glm::vec3(1.f, 1.f, 1.f));
		world->AddComponent<SDLSpriteAnimationDirection>(playerEntity);
		if (auto anim = world->AddComponent<SDLAnimatedSprite>(playerEntity, sdlTexturesManager->GetAsset("chopper"), 32, 32, 0, 0, 32, 32))
		{
			anim->InitAtimation(2, 30);
		}

		auto systems = ManagersProvider::Instance().GetSystemsManager();
		systems->Start();
	}

	void Game::Update()
	{
		ManagersProvider::Instance().Update();
		ManagersProvider::Instance().Draw();
	}
}

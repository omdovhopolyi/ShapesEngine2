
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
#include "Resources/OpenGLTexturesManager.h"
#include "Resources/ShadersManager.h"

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

		auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<OpenGLTexturesManager>();

		auto shadersManager = ManagersProvider::Instance().GetOrCreateAssetsManager<ShadersManager>();
		shadersManager->LoadAsset("SimpleShaderColor", ShadersManager::LoadParams{
			{ "vertexPath", "../assets/shaders/SimpleColor.vert" },
			{ "fragmentPath", "../assets/shaders/SimpleColor.frag" }
		});

		shadersManager->LoadAsset("SimpleShaderTex", ShadersManager::LoadParams{
			{ "vertexPath", "../assets/shaders/SimpleTex.vert" },
			{ "fragmentPath", "../assets/shaders/SimpleTex.frag" }
		});

		auto world = ManagersProvider::Instance().GetWorld();

		auto camera = world->CreateEntity();
		auto cameraComp = world->AddComponent<CameraComp>(camera);
		cameraComp->position = glm::vec3(0.f, 0.f, 5.f);

		auto tank1 = world->CreateEntity();
		auto sprite1 = world->AddComponent<Sprite>(tank1);
		sprite1->texture = texturesManager->GetAsset("tank");
		sprite1->texRect.origin = glm::vec2(0);
		sprite1->texRect.size = glm::vec2(32);
		sprite1->shader = "SimpleShaderTex";

		auto transform1 = world->AddComponent<Transform>(tank1);
		transform1->position = glm::vec3(0.f, 0.f, 0.f);
		transform1->rotation = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

		auto player = world->CreateEntity();
		auto playerSprite = world->AddComponent<Sprite>(player);
		playerSprite->texture = texturesManager->GetAsset("chopper");
		playerSprite->texRect.origin = glm::vec2(0);
		playerSprite->texRect.size = glm::vec2(32);
		playerSprite->shader = "SimpleShaderTex";

		auto playerTransform = world->AddComponent<Transform>(player);
		playerTransform->position = glm::vec3(1.f, 0.f, 0.f);
		playerTransform->rotation = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

		auto animation = world->AddComponent<SpriteFrameAnimation>(player);
		animation->frames.push_back({ glm::vec2(0), glm::vec2(32) });
		animation->frames.push_back({ glm::vec2(32, 0), glm::vec2(32) });
		animation->frameTime = 0.5f;

		/*auto tank1 = world->CreateEntity();
		world->AddComponent<Sprite>(tank1, texturesManager->GetAsset("tank"), glm::vec2(0, 0), glm::vec2(32, 32), "SimpleShaderTex");
		world->AddComponent<Transform>(tank1, glm::vec3(1.f, 0.f, 0.f), 0.f, glm::vec3(1.f, 1.f, 1.f));

		auto tank2 = world->CreateEntity();
		world->AddComponent<Sprite>(tank2, texturesManager->GetAsset("tank"), glm::vec2(0, 0), glm::vec2(32, 32), "SimpleShaderTex");
		world->AddComponent<Transform>(tank2, glm::vec3(0.f, 1.f, 0.f), 0.f, glm::vec3(1.f, 1.f, 1.f));*/

		/*auto sdlTexturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();
		sdlTexturesManager->LoadAsset("tank", "../assets/images/tank-panther-right.png");
		sdlTexturesManager->LoadAsset("tilemap", "../assets/tilemaps/jungle.png");
		sdlTexturesManager->LoadAsset("chopper", "../assets/images/chopper-spritesheet.png");
		sdlTexturesManager->LoadAsset("bullet", "../assets/images/bullet.png");

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
		world->AddComponent<RigidBody>(playerEntity, glm::vec3{}, 2.f);
		world->AddComponent<Transform>(playerEntity, glm::vec3(400.f, 320.f, 2.f), 0.f, glm::vec3(1.f, 1.f, 1.f));
		world->AddComponent<BoundingBox>(playerEntity, glm::vec3(32.f, 32.f, 0.f));
		world->AddComponent<SpriteAnimationDirection>(playerEntity);
		if (auto anim = world->AddComponent<SDLAnimatedSprite>(playerEntity, sdlTexturesManager->GetAsset("chopper"), 32, 32, 0, 0, 32, 32))
		{
			anim->InitAtimation(2, 30);
		}*/

		auto systems = ManagersProvider::Instance().GetSystemsManager();
		systems->Start();
	}

	void Game::Update()
	{
		ManagersProvider::Instance().Update();
		ManagersProvider::Instance().Draw();
	}
}

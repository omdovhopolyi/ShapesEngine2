#pragma once

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

#include "Resources/SDLTexturesManager.h"

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
			ProcessInput();
			Update();
		}
	}

	void Game::Destroy()
	{
		ManagersProvider::Instance().Clear();
	}

	void Game::Setup()
	{
		auto sdlTexturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();
		sdlTexturesManager->LoadAsset("tank", "../assets/images/tank-panther-right.png");

		RegisterSystems();

		auto world = ManagersProvider::Instance().GetWorld();

		auto entity = world->CreateEntity();
		world->AddComponent<Transform>(entity, glm::vec3(10.f, 20.f, 0.f), 45.f, glm::vec3(3.f, 3.f, 1.f));
		world->AddComponent<RigidBody>(entity, glm::vec3(100.f, 0.f, 0.f));
		auto& sprite = world->AddComponent<SDLSprite>(entity);
		sprite.width = 32;
		sprite.height = 32;
		sprite.rect.x = 0;
		sprite.rect.y = 0;
		sprite.rect.w = 32;
		sprite.rect.h = 32;

		auto systems = ManagersProvider::Instance().GetSystemsManager();
		systems->Start();
	}

	void Game::ProcessInput()
	{
		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_isRunning = false;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					_isRunning = false;
				}
				break;
			}

		}
	}

	void Game::Update()
	{
		ManagersProvider::Instance().Update();
	}
}

#pragma once

#include "Game.h"
#include "ManagersProvider.h"
#include "Logger/Logger.h"
#include "ECS/SystemsManager.h"
#include "ECS/EcsWorld.h"
#include "Time.h"
#include "GameWindow.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Velocity.h"

#include <iostream>

namespace shen
{
	Game::Game()
	{
		Logger::Log("Game constructor");
		Logger::Err("Checking problems logging");
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
		auto world = ManagersProvider::Instance().GetWorld();

		auto entity = world->CreateEntity();
		auto& transform = world->AddComponent<Transform>(entity);
		transform.position = { 10.f, 20.f, 0.f };

		auto& velocity = world->AddComponent<Velocity>(entity);
		velocity.velocity = { 100.f, 0.f, 0.f };
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

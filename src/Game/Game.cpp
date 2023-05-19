#pragma once

#include "Game.h"
#include "SDL_image.h"
#include "glm/glm.hpp"
#include "Logger/Logger.h"

#include <iostream>

namespace ShE
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
		const int result = SDL_Init(SDL_INIT_EVERYTHING);
		if (result != 0)
		{
			Logger::Err("Initializing SDL");
			return;
		}

		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);
		_winWidth = displayMode.w;
		_winHeight = displayMode.h;

		_window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_winWidth,
			_winHeight,
			SDL_WINDOW_BORDERLESS);

		if (!_window)
		{
			Logger::Err("Error creating window");
			return;
		}

		_renderer = SDL_CreateRenderer(_window, -1, 0);
		if (!_renderer)
		{
			Logger::Err("Error creating renderer");
			return;
		}

		SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		_isRunning = true;
	}

	void Game::Run()
	{
		Setup();

		while (_isRunning)
		{
			ProcessInput();
			Update();
			Render();
		}
	}

	void Game::Destroy()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	glm::vec2 position;
	glm::vec2 velocity;

	void Game::Setup()
	{
		position = { 10.f, 20.f };
		velocity = { 100.f, 0.f };
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
		int timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - _lastUpdateTime);
		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}
		
		float dt = (SDL_GetTicks() - _lastUpdateTime) / 1000.f;

		_lastUpdateTime = SDL_GetTicks();

		position += velocity * dt;
	}

	void Game::Render()
	{
		SDL_SetRenderDrawColor(_renderer, 21, 21, 21, 255);
		SDL_RenderClear(_renderer);

		SDL_Surface* surface = IMG_Load("../assets/images/tank-panther-right.png");
		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_FreeSurface(surface);

		SDL_Rect destRect = { 
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			32, 
			32 
		};

		SDL_RenderCopy(_renderer, texture, NULL, &destRect);

		SDL_DestroyTexture(texture);

		SDL_RenderPresent(_renderer);
	}
}

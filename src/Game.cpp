#pragma once

#include "Game.h"
#include "SDL_image.h"
#include "glm/glm.hpp"


#include <iostream>


namespace ShE
{
	Game::Game()
	{

	}

	Game::~Game()
	{

	}

	void Game::Initialize()
	{
		const int result = SDL_Init(SDL_INIT_EVERYTHING);
		if (result != 0)
		{
			std::cerr << "Error initializing SDL" << std::endl;
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
			std::cerr << "Error creating window" << std::endl;
			return;
		}

		_renderer = SDL_CreateRenderer(_window, -1, 0);
		if (!_renderer)
		{
			std::cerr << "Error creating renderer" << std::endl;
			return;
		}

		SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);

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
		velocity = { 0.1f, 0.05f };
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
		position += velocity;
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

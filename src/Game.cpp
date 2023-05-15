#pragma once

#include "Game.h"

#include <SDL.h>
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

		_window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			600,
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

		_isRunning = true;
	}

	void Game::Run()
	{
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

	}

	void Game::Render()
	{
		SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
		SDL_RenderClear(_renderer);


		SDL_RenderPresent(_renderer);
	}
}

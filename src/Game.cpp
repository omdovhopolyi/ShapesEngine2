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

		SDL_Window* window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			600,
			0);

		if (!window)
		{
			std::cerr << "Error creating window" << std::endl;
			SDL_Quit();
			return;
		}

		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

		if (!renderer)
		{
			std::cerr << "Error creating renderer" << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			return;
		}
	}

	void Game::Run()
	{
		/*while (true)
		{
			ProcessInput();
			Update();
			Render();
		}*/
	}

	void Game::Destroy()
	{

	}

	void Game::ProcessInput()
	{

	}

	void Game::Update()
	{

	}

	void Game::Render()
	{

	}
}

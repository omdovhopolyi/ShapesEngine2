#pragma once

#include "Game.h"

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

	}

	void Game::Run()
	{
		while (true)
		{
			ProcessInput();
			Update();
			Render();
		}
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

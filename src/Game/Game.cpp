
#include "Game.h"
#include "ManagersProvider.h"
#include "Logger/Logger.h"
#include "Time.h"
#include "GameWindow.h"
#include "MapLoader.h"

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

		/*_subscriptions.Subscribe<KeyEvent>([this](const auto& event)
		{
			if (event.type == KeyEventType::Up)
			{
				if (event.code == SDLK_ESCAPE)
				{
					_isRunning = false;
				}
			}
		});*/

		_subscriptions.Subscribe<Quit>([this](const auto& event)
		{
			_isRunning = false;
		});

		auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<OpenGLTexturesManager>();

		auto mapLoader = ManagersProvider::Instance().GetMapLoader();
		mapLoader->LoadMap("map_test");

		auto systems = ManagersProvider::Instance().GetSystemsManager();
		systems->Start();
	}

	void Game::Update()
	{
		ManagersProvider::Instance().Update();
		ManagersProvider::Instance().Draw();
	}
}

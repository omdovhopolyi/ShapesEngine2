#pragma once

#include <SDL.h>

namespace ShE
{
	class Game
	{
	public:
		Game();
		~Game();

		void Initialize();
		void Run();
		void Destroy();

	private:
		void Setup();
		void ProcessInput();
		void Update();
		void Render();

	private:
		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;
		int _winWidth = 800;
		int _winHeight = 600;
		bool _isRunning = false;
	};
}

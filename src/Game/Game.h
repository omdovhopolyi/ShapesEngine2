#pragma once

#include <SDL.h>

namespace ShE
{
	const int FPS = 60;
	const int MILLISEC_PER_FRAME = 1000 / FPS;

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
		int _lastUpdateTime = 0;
		bool _isRunning = false;
	};
}

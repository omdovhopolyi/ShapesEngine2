#pragma once

namespace shen
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

	private:
		int _lastUpdateTime = 0;
		bool _isRunning = false;
	};
}

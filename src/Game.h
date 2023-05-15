#pragma once

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
		void ProcessInput();
		void Update();
		void Render();
	};
}

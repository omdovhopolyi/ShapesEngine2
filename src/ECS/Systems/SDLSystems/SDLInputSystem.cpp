#include "SDLInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"

#include "Game/ManagersProvider.h"
#include "ECS/SystemsManager.h"
#include "SDLBoundingBoxDebugSystem.h"

namespace shen
{
	void SDLInputSystem::Update()
	{
		SDL_Event event;
		SDL_Keycode down;
		bool needAddDownKey = false;

		auto bbs = ManagersProvider::Instance().GetSystemsManager()->GetSystem<SDLBoundingBoxDebugSystem>();

		while (SDL_PollEvent(&event))
		{
			//ImGuiIO& io = ImGui::GetIO();

			if (bbs->IsActivated())
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
			}

			switch (event.type)
			{
			case SDL_QUIT:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<Quit>();
				break;
			}
			case SDL_KEYDOWN:
			{
				auto it = _holdKeys.find(event.key.keysym.sym);
				if (it == _holdKeys.end())
				{
					down = event.key.keysym.sym;
					needAddDownKey = true;
					ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Down, event.key.keysym.sym);
				}
				break;
			}
			case SDL_KEYUP:
			{
				_holdKeys.erase(event.key.keysym.sym);
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Up, event.key.keysym.sym);
				break;
			}
			/*case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					io.DisplaySize.x = static_cast<float>(event.window.data1);
					io.DisplaySize.y = static_cast<float>(event.window.data2);
				}
			}*/
			}

			/*int mouseX, mouseY;
			const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

			io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
			io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
			io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);*/
		}

		for (const auto& key : _holdKeys)
		{
			ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Hold, key);
		}

		if (needAddDownKey)
		{
			_holdKeys.insert(down);
		}
	}
}

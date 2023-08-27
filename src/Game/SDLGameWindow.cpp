#include "SDLGameWindow.h"
#include "Logger/Logger.h"

#include "imgui/imgui.h"
//#include "imgui/imgui_sdl.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"

namespace shen
{
	bool SDLGameWindow::Init()
	{
		const int result = SDL_Init(SDL_INIT_EVERYTHING);
		if (result != 0)
		{
			Logger::Err("Initializing SDL");
			return false;
		}

		//SDL_DisplayMode displayMode;
		//SDL_GetCurrentDisplayMode(0, &displayMode);

		//SetWidth(displayMode.w);
		//SetHeight(displayMode.h);

		_window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			GetWidth(),
			GetHeight(),
			SDL_WINDOW_BORDERLESS);

		if (!_window)
		{
			Logger::Err("Error creating window");
			return false;
		}

		_renderer = SDL_CreateRenderer(_window, -1, 0);
		if (!_renderer)
		{
			Logger::Err("Error creating renderer");
			return false;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}


		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
		ImGui_ImplSDLRenderer2_Init(_renderer);

		/*ImGui::CreateContext();
		ImGuiSDL::Initialize(_renderer, 800, 600);*/

		//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		return true;
	}

	void SDLGameWindow::Destroy()
	{
		//ImGuiSDL::Deinitialize();
		//ImGui::DestroyContext();

		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();

		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void SDLGameWindow::BeginFrame()
	{
		SDL_SetRenderDrawColor(_renderer, 21, 21, 21, 255);
		SDL_RenderClear(_renderer);
	}

	void SDLGameWindow::EndFrame()
	{
		SDL_RenderPresent(_renderer);

		/*ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}*/
	}
}

#include "EditorSystem.h"
#include "Messenger/Events/Common.h"
#include "Game/ManagersProvider.h"
#include "Game/OpenGLWindow.h"

#include "ECS/EcsWorld.h"
#include "ECS/Components/Render.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glad/glad.h"
#include <SDL.h>

namespace shen
{
    void EditorSystem::Start()
    {
        InitSubscriptions();
    }

    void EditorSystem::Update()
    {
        if (!_isInited)
        {
            return;
        }

        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("Editor");

        if (ImGui::Button("Demo"))
        {
            _demo = true;
        }

        if (ImGui::Button("Test window"))
        {
            _test = true;
        }

        ImGui::End();

        if (_demo)
        {
            ImGui::ShowDemoWindow(&_demo);
        }

        if (_test)
        {
            std::string components;

            auto world = ManagersProvider::Instance().GetWorld();
            auto entity = world->GetFirst<SpriteFrameAnimation>();

            if (world->IsValid(entity))
            {
                auto componentsIds = world->GetAllComponents(entity);

                for (const auto& compId : componentsIds)
                {
                    components += compId;
                    components += "\n";
                }
            }

            ImGui::Begin("Test window", &_test);
            ImGui::Text(components.c_str());
            ImGui::End();
        }

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
    }

    void EditorSystem::Stop()
    {
        DeinitImgui();
    }

    void EditorSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.type == InputEventType::Up)
            {
                if (event.code == static_cast<int>('e') && event.mode == KeyMode::Crtl)
                {
                    _isActive = !_isActive;

                    if (_isActive)
                    {
                        InitImgui();
                    }
                    else
                    {
                        DeinitImgui();
                    }
                }
            }
        });
    }

    void EditorSystem::InitImgui()
    {
        if (_isInited)
        {
            return;
        }

        auto window = dynamic_cast<OpenGLWindow*>(ManagersProvider::Instance().GetGameWindow());
        if (!window)
        {
            return;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigViewportsNoAutoMerge = true;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetContext());
        ImGui_ImplOpenGL3_Init("#version 130");

        _isInited = true;
    }

    void EditorSystem::DeinitImgui()
    {
        if (_isInited)
        {
            _isInited = false;
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
        }
    }
}

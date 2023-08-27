cmake_minimum_required(VERSION 3.20.4 FATAL_ERROR)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/submodules/imgui_sdl)

configure_file(${IMGUI_DIR}/imgui_sdl.h ${PROJECT_SOURCE_DIR}/src/imgui/imgui_sdl.h COPYONLY)
configure_file(${IMGUI_DIR}/imgui_sdl.cpp ${PROJECT_SOURCE_DIR}/src/imgui/imgui_sdl.cpp COPYONLY)

cmake_minimum_required(VERSION 3.20.4 FATAL_ERROR)

set(TARGET_NAME ShapesEngine2)

project(${TARGET_NAME})

#set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(cmake/imgui)

file (GLOB_RECURSE SRC_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(${TARGET_NAME} ${SRC_FILES})

foreach(source IN LISTS SRC_FILES)
    get_filename_component(source_path "${source}" DIRECTORY)
    string(REPLACE ${PROJECT_SOURCE_DIR} "" source_path "${source_path}")
    source_group("${source_path}" FILES "${source}")
endforeach()

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

set(ENTT_INCLUDE_NATVIS ON)

add_subdirectory(submodules/SDL)
target_link_libraries(${TARGET_NAME} SDL2 SDL2main)
#target_compile_options(SDL2 PUBLIC "$<$<CONFIG:DEBUG>:-g>")

add_subdirectory(submodules/SDL_image)
target_link_libraries(${TARGET_NAME} SDL2_image)

add_subdirectory(submodules/SDL_ttf)
target_link_libraries(${TARGET_NAME} SDL2_ttf)

add_subdirectory(submodules/SDL_mixer)
target_link_libraries(${TARGET_NAME} SDL2_mixer)

add_subdirectory(submodules/glm)
target_link_libraries(${TARGET_NAME} glm)

add_subdirectory(cmake/lua)
target_link_libraries(${TARGET_NAME} lua)

add_subdirectory(submodules/sol2)
target_link_libraries(${TARGET_NAME} sol2)

#add_subdirectory(external/glad)
#target_link_libraries(${TARGET_NAME} glad)

#add_subdirectory(submodules/assimp)
#target_link_libraries(${TARGET_NAME} assimp)

#add_subdirectory(submodules/reactphysics3d)
#target_link_libraries(${TARGET_NAME} reactphysics3d)

include_directories(src)

include_directories(submodules/imgui)
include_directories(submodules/SDL)
include_directories(submodules/SDL_image)
include_directories(submodules/SDL_ttf)
include_directories(submodules/SDL_mixer)
include_directories(submodules/glm)
include_directories(submodules/lua)
include_directories(submodules/sol2)
include_directories(submodules/spdlog/include)
include_directories(submodules/entt/src)

if (MSVC)
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/submodules/SDL/Debug/SDL2d.dll
                ${CMAKE_BINARY_DIR}/bin/Debug/SDL2d.dll
        )
        
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/submodules/SDL_image/Debug/SDL2_imaged.dll
                ${CMAKE_BINARY_DIR}/bin/Debug/SDL2_imaged.dll
        )
endif()



set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

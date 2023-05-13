cmake_minimum_required(VERSION 3.20.4 FATAL_ERROR)

set(TARGET_NAME ShapesEngine2)

project(${TARGET_NAME})

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

set(LUA_DIR ${PROJECT_SOURCE_DIR}/submodules/lua)

add_library(
    lua STATIC
    ${LUA_DIR}/lapi.c
    ${LUA_DIR}/lauxlib.c
    ${LUA_DIR}/lbaselib.c
    ${LUA_DIR}/lcode.c
    ${LUA_DIR}/lcorolib.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/ldebug.c
    ${LUA_DIR}/ldo.c
    ${LUA_DIR}/ldump.c
    ${LUA_DIR}/lfunc.c
    ${LUA_DIR}/lgc.c
    ${LUA_DIR}/linit.c
    ${LUA_DIR}/liolib.c
    ${LUA_DIR}/llex.c
    ${LUA_DIR}/lmathlib.c
    ${LUA_DIR}/lmem.c
    ${LUA_DIR}/loadlib.c
    ${LUA_DIR}/lobject.c
    ${LUA_DIR}/lopcodes.c
    ${LUA_DIR}/loslib.c
    ${LUA_DIR}/lparser.c
    ${LUA_DIR}/lstate.c
    ${LUA_DIR}/lstring.c
    ${LUA_DIR}/lstrlib.c
    ${LUA_DIR}/ltable.c
    ${LUA_DIR}/ltablib.c
    ${LUA_DIR}/ltm.c
    ${LUA_DIR}/lua.c
    ${LUA_DIR}/lundump.c
    ${LUA_DIR}/lutf8lib.c
    ${LUA_DIR}/lvm.c
    ${LUA_DIR}/lzio.c
)

set_target_properties(lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/submodules/lua)


add_subdirectory(submodules/SDL)
target_link_libraries(${TARGET_NAME} SDL2)

#add_subdirectory(submodules/imgui)
#target_link_libraries(${TARGET_NAME} imgui)

add_subdirectory(submodules/SDL_image)
target_link_libraries(${TARGET_NAME} SDL2_image)

add_subdirectory(submodules/SDL_ttf)
target_link_libraries(${TARGET_NAME} SDL2_ttf)

add_subdirectory(submodules/SDL_mixer)
target_link_libraries(${TARGET_NAME} SDL2_mixer)

add_subdirectory(submodules/glm)
target_link_libraries(${TARGET_NAME} glm)


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

add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/submodules/SDL/Debug/SDL2d.dll
                ${CMAKE_BINARY_DIR}/bin/Debug/SDL2d.dll
        )

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

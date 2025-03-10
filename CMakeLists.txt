cmake_minimum_required(VERSION 3.20.4 FATAL_ERROR)

set(TARGET_NAME ShapesEngine2)

project(${TARGET_NAME})

set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(cmake/tinyxml2)

file (GLOB_RECURSE SRC_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

option(SHEN_STATIC "Build static lib" OFF)

if(SHEN_STATIC)
    add_library(${TARGET_NAME} STATIC ${SRC_FILES})
else()
    add_executable(${TARGET_NAME} ${SRC_FILES})
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/assets
                ${PROJECT_BINARY_DIR}/bin/Debug/assets
                COMMENT "Copying assets"
        )

    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_SOURCE_DIR}/openal32.dll
                ${CMAKE_BINARY_DIR}/openal32.dll)
endif()

foreach(source IN LISTS SRC_FILES)
    get_filename_component(source_path "${source}" DIRECTORY)
    string(REPLACE ${PROJECT_SOURCE_DIR} "" source_path "${source_path}")
    source_group("${source_path}" FILES "${source}")
endforeach()

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

set(ENTT_INCLUDE_NATVIS ON CACHE BOOL "" FORCE)

set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)

set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
  
set(BEZIER_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(submodules/SFML)
target_link_libraries(${TARGET_NAME} sfml-graphics sfml-audio)

add_subdirectory(cmake/lua)
target_link_libraries(${TARGET_NAME} lua)

add_subdirectory(submodules/sol2)
target_link_libraries(${TARGET_NAME} sol2)

add_subdirectory(submodules/box2d)
target_link_libraries(${TARGET_NAME} box2d)

add_subdirectory(submodules/bezier)
target_link_libraries(${TARGET_NAME} bezier)

include_directories(src)

include_directories(submodules/SFML)
include_directories(submodules/lua)
include_directories(submodules/sol2)
include_directories(submodules/spdlog/include)
include_directories(submodules/entt/src)
include_directories(submodules/box2d/include)
include_directories(submodules/bezier)

add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)

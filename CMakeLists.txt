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

#set(ENTT_INCLUDE_NATVIS ON)



#add_subdirectory(external/glad)
#target_link_libraries(${TARGET_NAME} glad)

#add_subdirectory(submodules/assimp)
#target_link_libraries(${TARGET_NAME} assimp)

#add_subdirectory(submodules/reactphysics3d)
#target_link_libraries(${TARGET_NAME} reactphysics3d)

include_directories(src)
include_directories(submodules/glm)
#include_directories(submodules/stb)
#include_directories(submodules/rapidjson/include)
#include_directories(submodules/entt/src)
#include_directories(submodules/reactphysics3d/include)
#include_directories(submodules/assimp/include)
#include_directories(external/glad/include)


set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${TARGET_NAME}>/resources)

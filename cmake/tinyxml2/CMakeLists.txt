cmake_minimum_required(VERSION 3.20.4 FATAL_ERROR)

set(TINYXML2_DIR ${PROJECT_SOURCE_DIR}/submodules/tinyxml2)

configure_file(${TINYXML2_DIR}/tinyxml2.h ${PROJECT_SOURCE_DIR}/src/tinyxml2/tinyxml2.h COPYONLY)
configure_file(${TINYXML2_DIR}/tinyxml2.cpp ${PROJECT_SOURCE_DIR}/src/tinyxml2/tinyxml2.cpp COPYONLY)

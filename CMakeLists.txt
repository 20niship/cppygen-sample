cmake_minimum_required(VERSION 3.20)

project(pygentest LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_compile_options(-fPIC -std=c++20 -Wall -Wextra)

file(GLOB MAIN_SOURCES src/main.cpp)
file(GLOB SHELL_SOURCES lib/*.cpp)
file(GLOB SHELL_HEADERS lib/*.hpp)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

# Auto Generation
set(cppygen_generated_hpp ${CMAKE_CURRENT_BINARY_DIR}/cppygen_generated.hpp)
set(cppygen_generated_cpp ${CMAKE_CURRENT_BINARY_DIR}/cppygen_generated.cpp)
set(cppygen_config_file ${CMAKE_CURRENT_LIST_DIR}/cppygenconfig.toml)

# find_program(_CPPYGEN_GENERATOR cppygen)
set(_CPPYGEN_GENERATOR python3 -m cppygen)
message(${cppygen_config_file})

pybind11_add_module(${PROJECT_NAME} MODULE ${MAIN_SOURCES} ${SHELL_SOURCES}
                    ${cppygen_generated_cpp})

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC #
         pybind11::module #
         pybind11::lto #
         pybind11::windows_extras #
         ${MAIN_LINK_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib
                                           ${CMAKE_CURRENT_BINARY_DIR})

# pybind11_extension(${PROJECT_NAME}) pybind11_strip(${PROJECT_NAME})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES #
             INTERPROCEDURAL_OPTIMIZATION ON
             CXX_VISIBILITY_PRESET "hidden"
             VISIBILITY_INLINES_HIDDEN ON)

add_custom_command(
  OUTPUT ${cppygen_generated_hpp} ${cppygen_generated_cpp}
  COMMAND
    ${_CPPYGEN_GENERATOR} ARGS #
    --config_file ${cppygen_config_file} #
    --cwd ${CMAKE_CURRENT_LIST_DIR} #
    --include_directories $<TARGET_PROPERTY:${PROJECT_NAME},INCLUDE_DIRECTORIES> #
    --verbose
    DEPENDS ${SHELL_SOURCES} ${cppygen_config_file} ${SHELL_HEADERS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cppygen
  COMMENT
    "Generating CPPyGen Code To ${cppygen_generated_hpp} and ${cppygen_generated_cpp}"
  VERBATIM)

# vim:sw=2

cmake_minimum_required(VERSION 3.25)
project(learnopengl_notes)

set(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)

add_executable(hello_window "creating a window/main.cpp" utils/glad.c)
# https://leimao.github.io/blog/CMake-Public-Private-Interface/
target_link_libraries(hello_window -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

add_executable(notes cpp_notes/main.cpp)
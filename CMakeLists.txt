cmake_minimum_required(VERSION 3.25)
project(learnopengl_notes)

set(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)

add_executable(hello_window "Hello Window/main.cpp" utils/glad.c)
# https://leimao.github.io/blog/CMake-Public-Private-Interface/
target_link_libraries(hello_window -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

add_executable(hello_triangle "Hello Triangle/triangle_main.cpp" utils/glad.c
        "Hello Triangle/triangle.h"
        "Hello Triangle/processors.cpp"
)
target_link_libraries(hello_triangle -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

add_executable(notes cpp_notes/main.cpp)

add_executable(math math/main.cpp)

add_executable(2nd_trianlge "Hello Triangle/2nd_trianlge.cpp" utils/glad.c
        "Hello Triangle/triangle.h"
        "Hello Triangle/processors.cpp"
)
target_link_libraries(2nd_trianlge -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

add_executable(rectangle "Hello Rectangle/rectangle.cpp" "Hello Rectangle/rectangle.h"
        "Hello Rectangle/utils.cpp"
        utils/glad.c
)
target_link_libraries(rectangle -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

add_executable(hexagram hexagram/hexagram.cpp hexagram/hexagram.h utils/glad.c
        hexagram/utils.cpp)
target_link_libraries(hexagram -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

add_executable(hexagram2 hexagram/hexagram2.cpp hexagram/hexagram.h utils/glad.c hexagram/utils.cpp)
target_link_libraries(hexagram2 -lopengl32 ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)

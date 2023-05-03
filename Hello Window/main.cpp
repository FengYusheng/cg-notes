#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 968;

int main()
{
    int glfw_major = 0;
    int glfw_minor = 0;
    int glfw_rev = 0;

    glfwInit();
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);

    std::cout << "GLFW library compile information: " << glfwGetVersionString() << std::endl;
    std::cout << "GLFW version information: " << glfw_major << "." << glfw_minor << "." << glfw_rev << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    glfwTerminate();
    return 0;
}
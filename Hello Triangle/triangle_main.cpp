#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

int main()
{
    int glfw_major = 0;
    int glfw_minor = 0;
    int glfw_rev = 0;

    /*
     * Initialization hints
     * https://www.glfw.org/docs/latest/intro_guide.html#init_hints
     * The values you set hints to are never reset by GLFW, but they only take effect during initialization.
     * Once GLFW has been initialized, any values you set will be ignored until the library is terminated and initialized again.
     */
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    glfwInit();
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);

    std::cout << "glfw version: " << glfw_major << "." << glfw_minor << "." << glfw_rev <<std::endl;
    std::cout << glfwGetVersionString() << std::endl;

    glfwTerminate();
    return 0;
}
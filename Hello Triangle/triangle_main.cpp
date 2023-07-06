#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 920;

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

    /*
     * Window creation hints
     * https://www.glfw.org/docs/latest/window_guide.html#window_hints
     *
     * How to get the window hints?
     */
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    /*
     * forward and backward compatible
     * https://www.zhihu.com/question/47239021/answer/524159893
     */
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif



    glfwTerminate();
    return 0;
}
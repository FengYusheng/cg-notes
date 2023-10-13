#include "glad/glad.h"
#include "GLFW/glfw3.h"

# include <iostream>

#include "rectangle.h"

int main()
{
    int glfw_major;
    int glfw_minor;
    int glfw_rev;

    glfwInit();

    /* compilation-time version */
    std::cout << "GLFW compilation-time version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

    /* run-time version */
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);
    std::cout << "GLFW run-time version: " << glfw_major << "." << glfw_minor << "." << glfw_rev << std::endl;

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Rectangle", NULL, NULL);
    if(NULL == window)
    {
        std::cout << "Failed to create a glfw window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }



    /*
     * glfw timer
     * https://www.glfw.org/docs/3.0/group__time.html
     */
    std::cout << glfwGetTime() << std::endl;

    glfwTerminate();
    return 0;
}

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 968;

int main()
{
    int glfw_major = 0;
    int glfw_minor = 0;
    int glfw_rev = 0;

    /*
     * glfw initialization and termination
     * https://www.glfw.org/docs/latest/intro_guide.html#intro_init
     */
    glfwInit();
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);

    std::cout << "GLFW library compile information: " << glfwGetVersionString() << std::endl;
    std::cout << "GLFW version information: " << glfw_major << "." << glfw_minor << "." << glfw_rev << std::endl;

    /*
     * glfw window creation hints
     * https://www.glfw.org/docs/latest/window_guide.html#window_hints
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    /*
     * glfw window creation
     * https://www.glfw.org/docs/latest/window_guide.html#window_creation
     */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Window", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "Failed to create a GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    /*
     * Assign opengl context to this glfw window.
     */
    glfwMakeContextCurrent(window);
    /*
     * double buffers
     */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    /*
     * event processing
     * https://www.glfw.org/docs/latest/input_guide.html#events
     */
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        /*opengl color buffer*/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*glfw initialization and termination
    * https://www.glfw.org/docs/latest/intro_guide.html#intro_init
    */
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
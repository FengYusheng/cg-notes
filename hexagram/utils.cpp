#include "GLFW/glfw3.h"

void processInput(GLFWwindow *window)
{
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if(GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow *window, GLuint width, GLuint height)
{
    glViewport(0, 0, width, height);
}
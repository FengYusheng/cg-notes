#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "hexagram.h"

int main()
{
    int glfw_major;
    int glfw_minor;
    int glfw_rev;
    GLuint vertexShader;
    GLuint fragmentShaderOrange;
    GLuint fragmentShaderYellow;
    GLuint shaderProgramOrange;
    GLuint shaderProgramYellow;
    GLint is_success;
    GLuint VAOs[2] = {0};
    GLuint VBOs[2] = {0};
    GLchar infoLog[512] = {0};

    std::cout << "GLFW compile-time version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);
    std::cout << "GLFW run-time version: " << glfw_major << "." << glfw_minor << "." << glfw_rev << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My 3rd Hexagram", NULL, NULL);
    if(NULL == window)
    {
        std::cout << "ERROR::GLFW::WINDOW CREATION FAILED!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::GLAD::INITIALIZATION FAILED!" << std::endl;
        glfwTerminate();
        return -1;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &is_success);
    if(!is_success)
    {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX SHADER::COMPILATION FAILED!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &orangeFragmentShaderSource, NULL);
    glCompileShader(fragmentShaderOrange);
    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &is_success);
    if(!is_success)
    {
        glGetShaderInfoLog(fragmentShaderOrange, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::ORANGE::COMPILATION FAILED!\n" << infoLog << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &yellowFragmentShaderSource, NULL);
    glCompileShader(fragmentShaderYellow);
    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &is_success);
    if(!is_success)
    {
        glGetShaderInfoLog(fragmentShaderYellow, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::FRAGMENT SHADER::YELLOW::COMPILATION FAILED!\n" << infoLog << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &is_success);
    if(!is_success)
    {
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::ORANGE TRIANGLE::LINKING FAILED!\n" << infoLog << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &is_success);
    if(!is_success)
    {
        glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::YELLOW TRIANGLE::LINKING FAILED!\n" << infoLog << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
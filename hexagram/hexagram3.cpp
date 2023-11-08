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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(orangeTriangle), orangeTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(yellowTriangle), yellowTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);
    glDeleteVertexArrays(sizeof(VAOs), VAOs);
    glDeleteBuffers(sizeof(VBOs), VBOs);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
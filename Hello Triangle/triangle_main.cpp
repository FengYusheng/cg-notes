#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 920;

const char *vertexShaderSource = "#version 460 core\n"
                                 "\n"
                                 "layout (location=0) in vec3 aPos;\n"
                                 "\n"
                                 "void main() {\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}";

const char* fragmentSahderSource = "#version 460 core\n"
                                   "\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main() {\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}";

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    int glfw_major = 0;
    int glfw_minor = 0;
    int glfw_rev = 0;
    int success = 0;
    char infoLog[512] = {0};

    /* vertex data and attribute configuration */
    float vertices[] = {
            -0.5f, -0.5, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    unsigned int VAO;

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
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    /*
     * https://www.glfw.org/docs/latest/window_guide.html#GLFW_CONTEXT_RELEASE_BEHAVIOR_hint
     */
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

    /*
     * What exactly is an "OpenGL Context"? How does it work?
     * https://www.gamedev.net/forums/topic/603708-what-exactly-is-an-opengl-context-how-does-it-work/
     */
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

    /*
     * forward and backward compatible
     * https://www.zhihu.com/question/47239021/answer/524159893
     */
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    /*
     * Full screen window
     * https://www.glfw.org/docs/latest/window_guide.html#window_full_screen
     *
     * GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle", glfwGetPrimaryMonitor(), NULL);
     */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "Failed to create a glfw window." << std::endl;
        glfwTerminate();
        return -1;
    }

    /*
     * https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157
     * This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread.
     * A context must only be made current on a single thread at a time and each thread can have only a single current
     * context at a time.
     */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Build and compile the shader program. */

    /* vertex shader */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* fragment shader */
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSahderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* link shaders */
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    /* The shader objects are useless after linking.
     * If a shader object to be deleted is attached to a program object, it will be flagged for deletion,
     * but it will not be deleted until it is no longer attached to any program object, for any rendering context
     * (i.e., it must be detached from wherever it was attached before it will be deleted).
     */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    /*
     * Bind the VAO first, any subsequence VBO, EBO, glVertexAttribPointer and glEnableVertexAttribArray calls
     * will be stored in inside the VAO currently bound.
     *
     * When we say a vertex, we are saying the position, color, depth and any other information for this vertex. These
     *  various kinds of information are called "vertex attributes".
     */
    glBindVertexArray(VAO);
    /* GL_ARRAY_BUFFER, vertex attributes */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
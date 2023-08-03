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

    /*
     * https://learnopengl.com/Getting-started/Hello-Triangle
     * 1. The first parameter specifies which vertex attribute we want to configure.
     *    Remember that we specified the location of the position vertex attribute in the vertex shader with
     *    layout (location = 0). This sets the location of the vertex attribute to 0 and since we want to pass data
     *    to this vertex attribute, we pass in 0.
     *
     * 2. The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3
     *    so it is composed of 3 values.
     *
     * 3. The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL consists of floating
     *    point values).
     *
     * 4. The next argument specifies if we want the data to be normalized. If we're inputting integer data types
     *    (int, byte) and we've set this to GL_TRUE, the integer data is normalized to 0 (or -1 for signed data) and
     *    1 when converted to float. This is not relevant for us so we'll leave this at GL_FALSE.
     *
     * 5. The fifth argument is known as the stride and tells us the space between consecutive vertex attributes.
     *    Since the next set of position data is located exactly 3 times the size of a float away we specify that
     *    value as the stride. Note that since we know that the array is tightly packed (there is no space between
     *    the next vertex attribute value) we could've also specified the stride as 0 to let OpenGL determine the
     *    stride (this only works when values are tightly packed). Whenever we have more vertex attributes we have to
     *    carefully define the spacing between each vertex attribute but we'll get to see more examples of that later on.
     *
     * 6. The last parameter is of type void* and thus requires that weird cast. This is the offset of where the
     *    position data begins in the buffer. Since the position data is at the start of the data array this value
     *    is just 0.
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*
     * note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound
     * vertex buffer object so afterwards we can safely unbind.
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*
     * You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens.
     * Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs)
     * when it's not directly necessary.
     */
    glBindVertexArray(0);

    /* Uncomment this call to draw in wireframe polygons.
     * GL_FILL
     * GL_LINE
     * GL_POINT
     */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        /* Seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized. */
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* Optional: de-allocate all resources once they've outlived their purpose. */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

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
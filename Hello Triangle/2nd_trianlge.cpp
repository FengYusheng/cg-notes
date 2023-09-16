#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "triangle.h"

#include "iostream"

int main()
{
    /*
    * GLFW version management
    * https://www.glfw.org/docs/latest/intro_guide.html#intro_version
    */
    int glfw_major = 0;
    int glfw_minor = 0;
    int glfw_rev = 0;

    /* compile-time version */
    std::cout << "GLFW compile-time version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
    std::cout << "GLFW compile-time verbose version info: " << glfwGetVersionString() << std::endl;

    /* run-time version */
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);
    std::cout << "GLFW run-time version: " << glfw_major << "." << glfw_minor << "." << glfw_rev << std::endl;

    /* Initialization hints */
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    glfwInit();

    /* Creation hints */
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    /*
     * Stereo rendering unavailable
     * https://discourse.glfw.org/t/glfw-stereo/188
     *
     * glfwWindowHint(GLFW_STEREO, GLFW_TRUE);
     */
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    /* Create shader objects and load shader source codes to shader objects */

    /* Compile shaders */

    /* Create a program object and attach shader objets to that program object */

    /* Link shaders */

    /* Delete shader objects after linking shaders */

    /* Load data to the shader program from CPU to GPU */

    /* Generate buffer objects, such as VAO, VBO, EBO and so on */

    /* Bind a VAO first */

    /* Bind a VBO and load vertex data to it */

    /* Set vertex attributes' pointers and enable vertex attributes */

    /* Unbind VAO and VBO */

    /* Select a polygon rasterization mode */

    /* Windows creation and  event processing */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My 2nd Triangle", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "Failed to create a glfw window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* This step must be below the above 2 steps. */
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* Bind a VAO and draw the scene */

    /* Window destruction and termination */
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

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

    /* Event processing */

    /* Bind a VAO and draw the scene */

    /* Window destruction and termination */

    glfwTerminate();
    return 0;
}

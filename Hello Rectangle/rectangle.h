#ifndef LEARNOPENGL_NOTES_RECTANGLE_H
#define LEARNOPENGL_NOTES_RECTANGLE_H

const static char *vertexShaderSource = "#version 460 core\n"
                                        "\n"
                                        "layout (location=0) in vec3 aPos;\n"
                                        "\n"
                                        "void main() {\n"
                                        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                        "}";

const static char *fragmentShaderSource = "#version 460 core\n"
                                          "\n"
                                          "out vec4 fragColor;\n"
                                          "\n"
                                          "void main() {\n"
                                          "    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                          "}";

const static unsigned int WIDTH = 800;
const static unsigned int HEIGHT = 600;

extern void processInput(GLFWwindow *window);
extern void framebuffer_size_callback(GLFWwindow *window, int width, int height);

#endif

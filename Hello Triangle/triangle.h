#ifndef LEARNOPENGL_NOTES_TRIANGLE_H
#define LEARNOPENGL_NOTES_TRIANGLE_H

/*
 * 关于关键字static和extern的详细用法
 * https://blog.csdn.net/qq_46329012/article/details/124535942
 */

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


extern void processInput(GLFWwindow* window);
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //LEARNOPENGL_NOTES_TRIANGLE_H

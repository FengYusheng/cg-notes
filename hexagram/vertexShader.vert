#version 460 core

layout (location=0) in vec3 aPos;

void main() {
    gl_Posistion = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
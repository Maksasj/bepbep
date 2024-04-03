#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

layout (location = 0) out vec4 outColor;

uniform mat4 translation;
uniform mat4 scale;
uniform mat4 rotation;

uniform mat4 proj;
uniform mat4 view;

void main() {
    gl_Position = proj * view * /* translation * rotation *  scale * */ vec4(aPos, 1.0);
    outColor = aColor;
}
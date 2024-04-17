#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCord;

layout (location = 0) out vec3 oPos;
layout (location = 1) out vec3 oNormal;
layout (location = 2) out vec2 oTexCord;

void main() {
    gl_Position = vec4(aPos, 1.0);

    oPos = aPos;
    oNormal = aNormal;
    oTexCord = aTexCord;
}
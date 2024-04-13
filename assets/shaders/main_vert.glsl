#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCord;

layout (location = 0) out vec3 oPos;
layout (location = 1) out vec3 oNormal;
layout (location = 2) out vec2 oTexCord;

uniform mat4 transform;

uniform vec3 camPos;
uniform mat4 proj;
uniform mat4 view;

void main() {
    vec4 model = transform * vec4(aPos, 1.0);
    gl_Position = proj * view * model;

    oPos = model.xyz;
    oNormal = aNormal;
    oTexCord = aTexCord;
}
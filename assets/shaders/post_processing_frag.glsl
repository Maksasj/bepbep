#version 450 core

layout (location = 0) out vec4 fragColor;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCord;

uniform sampler2D image;

void main() {
    vec3 color = texture(image, aTexCord).rgb;

    fragColor = vec4(color, 1.0f);
}
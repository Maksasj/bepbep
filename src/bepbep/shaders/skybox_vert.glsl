#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 0) out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;

void main() {
    TexCoords = aPos;

    mat4 newView = view;

    for(int i = 0; i < 3; ++i) {
        newView[i][3] = 0;
        newView[3][i] = 0;
    }

    gl_Position = proj * newView * vec4(aPos, 1.0);
}

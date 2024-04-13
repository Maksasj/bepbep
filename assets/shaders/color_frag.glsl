#version 450 core

layout (location = 0) out vec4 fragColor;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;

struct Light {
    vec3 origin;
};

layout(binding = 0) uniform Lights {
    int lightCount;
    Light sources[16];
};

uniform vec3 camPos;

void main() {
    vec3 normal = normalize(aNormal);

    float ambient = 0.1f;
    float diffuse = 0;
    float specular = 0;

    for(int i = 0; i < lightCount; ++i) {
        Light light = sources[i];

        // Diffuse light
        vec3 lightDirection = normalize(light.origin - aPos);
        diffuse += max(dot(normal, lightDirection), 0.0f);

        // Specular light
        float specularLight = 0.50f;
        vec3 viewDirection = normalize(camPos - light.origin);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);

        specular += specAmount * specularLight;
    }

    fragColor = vec4(aColor.rgb * (diffuse + ambient + specular), 1.0f);
}
#version 450 core

layout (location = 0) out vec4 fragColor;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCord;

layout (location = 3) in vec3 aFragPos;

layout (binding = 0) uniform sampler2D albedoMap;
layout (binding = 1) uniform sampler2D aoMap;
layout (binding = 2) uniform sampler2D metallicMap;
layout (binding = 3) uniform sampler2D normalMap;
layout (binding = 4) uniform sampler2D roughnessMap;
layout (binding = 5) uniform samplerCube environmentMap;

struct Light {
    vec3 origin;
    int padding;
    vec4 color;
};

float PI = 3.14159;

layout(binding = 0) uniform Lights {
    int lightCount;
    Light sources[16];
};

uniform vec3 camPos;
vec3 emissivityMesh = vec3(0.0);

float D(float alpha, vec3 N, vec3 H) {
    float numerator = pow(alpha, 2.0);

    float NdotH = max(dot(N, H), 0.0);
    float denominator = PI * pow(pow(NdotH, 2.0) * (pow(alpha, 2.0) - 1.0) + 1.0, 2.0);

    denominator = max(denominator, 0.000001);

    return numerator / denominator;
}

float G1(float alpha, vec3 N, vec3 X) {
    float numerator = max(dot(N, X), 0.0);

    float k = alpha / 2.0f;

    float denominator = max(dot(N, X), 0.0) * (1.0 - k) + k;
    denominator = max(denominator, 0.000001);

    return numerator / denominator;
}

float G(float alpha, vec3 N, vec3 V, vec3 L) {
    return G1(alpha, N, V) * G1(alpha, N, L);
}

vec3 F(vec3 F0, vec3 V, vec3 H) {
    return F0 + (vec3(1.0) - F0) * pow(1 - max(dot(V, H), 0.0), 5.0);
}

float ao = texture(aoMap, aTexCord).r;
vec3 albedoMesh = texture(albedoMap, aTexCord).rgb;
float roughness = texture(roughnessMap, aTexCord).r;
float metallic = texture(metallicMap, aTexCord).r;
float alpha = pow(roughness, 2);

vec3 PBR(Light light) {
    vec3 N = normalize(aNormal);
    vec3 V = normalize(camPos - aFragPos);
    vec3 L = normalize(light.origin - aFragPos);

    if(light.padding != 0)
        L = vec3(0.0, 1.0, 0.0);

    vec3 H = normalize(V + L);

    // 0.04 is a dielectring thing
    vec3 F0 = mix(vec3(0.04, 0.04, 0.04), albedoMesh, metallic);

    vec3 Ks = F(F0, V, H);
    vec3 Kd = vec3(1.0) - Ks;
    Kd *= 1.0 - metallic;

    vec3 lambert = albedoMesh / PI;

    vec3 cookTorranceNumerator = D(alpha, N, H) * G(alpha, N, V, L) * F(F0, V, H);
    float cookTorranceDenominator = 4.0 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0);
    cookTorranceDenominator = max(cookTorranceDenominator, 0.000001);
    vec3 cookTorrance = cookTorranceNumerator / cookTorranceDenominator;

    vec3 BRDF = Kd * lambert + cookTorrance;
    return BRDF * light.color.rgb * max(dot(L, N), 0.0);
}

void main() {
    vec3 Lo = vec3(0.0);
    vec3 V = normalize(camPos - aFragPos);
    vec3 N = normalize(aNormal);

    for(int i = 0; i < lightCount; ++i) {
        Light light = sources[i];
        Lo += PBR(light);
    }

    vec3 R = normalize(reflect(normalize(aFragPos - camPos), N));
    vec3 envColor = texture(environmentMap, R).rgb / 100.0;

    Light light;
    light.origin = aFragPos + R;
    light.padding = 0;
    light.color = vec4(envColor, 0.0);

    Lo += PBR(light);


    /*
    vec3 F0 = mix(vec3(0.04, 0.04, 0.04), albedoMesh, metallic);
    vec3 envColor = texture(environmentMap, reflect(normalize(aFragPos - camPos), N)).rgb;
    // envColor = envColor / (envColor + vec3(1.0));
    // envColor = pow(envColor + 0.5, vec3(2));

    vec3 kS = F(F0, V, aNormal);
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;
    vec3 irradiance = envColor;
    vec3 diffuse = irradiance * albedoMesh;
    vec3 ambient = (kD * diffuse); // * ao;
    */

    vec3 color = Lo;
    // vec3 color = emissivityMesh + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    fragColor = vec4(color , 1.0);
}
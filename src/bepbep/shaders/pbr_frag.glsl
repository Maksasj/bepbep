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

struct Light {
    vec3 origin;
};

float PI = 3.14159;

layout(binding = 0) uniform Lights {
    int lightCount;
    Light sources[16];
};

uniform vec3 camPos;

vec3 fragmentPosition = aFragPos;
// vec3 normal = texture(normalMap, aTexCord).xyz * 0.5 + vec3(0.5);
vec3 normal = aNormal;
vec3 cameraPosition = camPos;
vec3 lightPosition = vec3(0.0, 5.0, 0.0);
vec3 lightColor = vec3(1.0);
vec3 albedoMesh = texture(albedoMap, aTexCord).rgb;
vec3 emissivityMesh = vec3(0.05);
float roughness = texture(roughnessMap, aTexCord).r;
vec3 baseReflectance = vec3(0.2);

float metallic = texture(metallicMap, aTexCord).r;

float alpha = pow(roughness, 2);

vec3 F0 = mix(vec3(0.04, 0.04, 0.04), albedoMesh, metallic);

vec3 N = normalize(normal);
vec3 V = normalize(cameraPosition - fragmentPosition);

// vec3 L = normalize(lightPosition);
vec3 L = normalize(lightPosition - fragmentPosition);
vec3 H = normalize(V + L);

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

vec3 PBR() {
    vec3 Ks = F(F0, V, H);
    vec3 Kd = vec3(1.0) - Ks;

    vec3 lambert = albedoMesh / PI;

    vec3 cookTorranceNumerator = D(alpha, N, H) * G(alpha, N, V, L) * F(F0, V, H);
    float cookTorranceDenominator = 4.0 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0);
    cookTorranceDenominator = max(cookTorranceDenominator, 0.000001);
    vec3 cookTorrance = cookTorranceNumerator / cookTorranceDenominator;

    vec3 BRDF = Kd * lambert + cookTorrance;
    return emissivityMesh + BRDF * lightColor * max(dot(L, N), 0.0);
}

void main() {
    vec3 pbr = PBR();

    fragColor = vec4(pbr, 1.0);
}
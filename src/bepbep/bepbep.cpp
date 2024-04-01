#include <vector>

#include "mesh.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

using namespace bepbep;

const std::vector<Vertex> vertices {
    {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}},
    {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}}
};

const std::vector<u32> indices {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

struct Transform {
    Mat4f translation;
    Mat4f scale;
    Mat4f rotation;
};

struct Camera {
    Mat4f proj;
    Mat4f view;
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("BepBep", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    auto vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();

    Mesh cube(vertices, indices);

    GLUniformBufferObject transformUbo(sizeof(Transform));
    GLUniformBufferObject cameraUbo(sizeof(Camera));

    transformUbo.bind();
    shaderProgram.bind_buffer("Transform", 0, transformUbo);
    auto transformPtr = static_cast<Transform*>(transformUbo.map());
    transformPtr->translation = Mat4f::translation(Vec3f::zero);
    transformPtr->scale = Mat4f::identity();

    cameraUbo.bind();
    shaderProgram.bind_buffer("Camera", 1, cameraUbo);
    auto cameraPtr = static_cast<Camera*>(cameraUbo.map());
    cameraPtr->proj = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);
    cameraPtr->view = Mat4f::translation(Vec3f(0, 0, 5));
    cameraUbo.unmap();
    cameraUbo.unbind();

    GLContext::enable(GL_DEPTH_TEST);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.enable();

        cube.render();

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    transformUbo.unmap();
    transformUbo.unbind();

    shaderProgram.destroy();

    GLFWContext::terminate();

    return 0;
}
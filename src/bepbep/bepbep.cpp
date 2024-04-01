#include <vector>

#include "mesh.h"
#include "camera.h"

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

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("BepBep", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    auto vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
    auto fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();

    Mesh cube(vertices, indices);

    shaderProgram.enable();
    shaderProgram.set_uniform("translation", Mat4f::translation(Vec3f::zero));
    shaderProgram.set_uniform("scale", Mat4f::identity());
    shaderProgram.set_uniform("rotation", trait_bryan_angle_yxz(Vec3f::zero));

    Camera camera({-5, 0, 0}, 100.0f);

    GLContext::enable(GL_DEPTH_TEST);

    while (!window->closing()) {
        camera.update(window);

        GLContext::set_viewport(0, 0, window->get_width(), window->get_height());
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.enable();

        camera.bind(shaderProgram);
        cube.render();

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    shaderProgram.destroy();

    GLFWContext::terminate();

    return 0;
}
#include "structure.h"
#include "camera.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

using namespace bepbep;

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("BepBep", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    auto vertexShader = GLShaderFactory::create_shader("shaders/main_vert.glsl", ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
    auto fragmentShader = GLShaderFactory::create_shader("shaders/main_frag.glsl", ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();

    shaderProgram.enable();

    Camera camera({-5, 0, 0}, 100.0f);

    Structure structure;

    GLContext::enable(GL_DEPTH_TEST);

    GLContext::enable(GL_CULL_FACE);
    GLContext::cull_face(GL_BACK);
    GLContext::front_face(GL_CCW);

    while (!window->closing()) {
        camera.update(window);

        GLContext::set_viewport(0, 0, window->get_width(), window->get_height());
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.enable();

        camera.bind(shaderProgram);

        structure.render(shaderProgram);

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    shaderProgram.destroy();

    GLFWContext::terminate();

    return 0;
}
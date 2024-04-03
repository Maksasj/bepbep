#include "bepbep.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

namespace bepbep {
    void BepBepApp::preinit() {
        GLFWContext::init();
    }

    void BepBepApp::init() {
        window = WindowFactory::create_window("BepBep", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

        GLContext::load_opengl();
        GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    }

    void BepBepApp::load() {
        auto vertexShader = GLShaderFactory::create_shader("shaders/main_vert.glsl", ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
        auto fragmentShader = GLShaderFactory::create_shader("shaders/main_frag.glsl", ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);

        shader = std::make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        vertexShader.destroy();
        fragmentShader.destroy();
    }

    void BepBepApp::run() {
        GraphicsContext context;

        context.set_debug_mode(true);
        context.set_main_shader(shader.get());
        context.set_line_shader(nullptr);

        shader->enable();

        Camera camera({-5, 0, 0}, 100.0f);

        Level level;

        GLContext::enable(GL_DEPTH_TEST);

        GLContext::enable(GL_CULL_FACE);
        GLContext::cull_face(GL_BACK);
        GLContext::front_face(GL_CCW);

        while (!window->closing()) {
            camera.update(window);

            GLContext::set_viewport(0, 0, window->get_width(), window->get_height());
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader->enable();

            camera.bind(*shader);

            level.render(context);

            GLFWContext::swap_buffers(*window);
            GLFWContext::poll_events();
        }
    }

    void BepBepApp::cleanup() {
        shader->destroy();

        GLFWContext::terminate();
    }
}
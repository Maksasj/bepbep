#include "bepbep.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

namespace bepbep {
    void BepBepApp::preinit() {
        GLFWContext::init();
    }

    void BepBepApp::init() {
        window = WindowFactory::create_window("BepBep", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL, {
            .enableResize = true
        });

        GLContext::load_opengl();
        GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        manager = make_unique<GameManager>();
    }

    void BepBepApp::load() {
        manager->load();
    }

    void BepBepApp::run() {
        GLContext::enable(GL_DEPTH_TEST);
        GLContext::enable(GL_CULL_FACE);
        GLContext::cull_face(GL_BACK);
        GLContext::front_face(GL_CW);

        f64 currentFrame = glfwGetTime();
        f64 lastFrame = currentFrame;

        while (!window->closing()) {
            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            GLContext::set_viewport(0, 0, window->get_width(), window->get_height());
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            manager->run(deltaTime);

            GLFWContext::swap_buffers(*window);
            GLFWContext::poll_events();
        }
    }

    void BepBepApp::cleanup() {
        GLFWContext::terminate();
    }
}
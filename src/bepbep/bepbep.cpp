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
    }

    std::shared_ptr<GLShaderProgram> BepBepApp::load_shader(const std::string& vertPath, const std::string& fragPath) {
        auto vertexShader = GLShaderFactory::create_shader(vertPath, ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
        auto fragmentShader = GLShaderFactory::create_shader(fragPath, ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);

        std::shared_ptr<GLShaderProgram> shader = std::make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        vertexShader.destroy();
        fragmentShader.destroy();

        return shader;
    }

    void BepBepApp::load() {
        mainShader = load_shader("shaders/main_vert.glsl", "shaders/main_frag.glsl");
        lineShader = load_shader("shaders/line_vert.glsl", "shaders/line_frag.glsl");
    }

    void BepBepApp::run() {
        GraphicsContext context;

        context.set_debug_mode(true);
        context.set_main_shader(mainShader.get());
        context.set_line_shader(lineShader.get());

        // Todo
        context.init_line_mesh();
        context.init_circle_mesh();

        mainShader->enable();
        Camera camera({-5, 0, 0}, 100.0f);

        LightManager light;
        light.add_light({Vec3f{0, 10, 0}});
        light.bind(context);

        Level level;

        GLContext::enable(GL_DEPTH_TEST);

        GLContext::enable(GL_CULL_FACE);
        GLContext::cull_face(GL_BACK);
        GLContext::front_face(GL_CW);

        double currentFrame = glfwGetTime();
        double lastFrame = currentFrame;
        double deltaTime;

        while (!window->closing()) {
            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            level.update(deltaTime);
            camera.update(window);

            GLContext::set_viewport(0, 0, window->get_width(), window->get_height());
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mainShader->enable();
            camera.bind(*mainShader);

            lineShader->enable();
            camera.bind(*lineShader);
            light.render(context);

            level.render(camera, context);

            GLFWContext::swap_buffers(*window);
            GLFWContext::poll_events();
        }
    }

    void BepBepApp::cleanup() {
        mainShader->destroy();
        lineShader->destroy();

        GLFWContext::terminate();
    }
}
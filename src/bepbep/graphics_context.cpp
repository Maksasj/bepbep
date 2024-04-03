#include "graphics_context.h"

namespace bepbep {
    GraphicsContext::GraphicsContext()
        : debugMode(false),
          mainShader(nullptr),
          lineShader(nullptr)
    {

    }

    void GraphicsContext::set_debug_mode(const bool& value) {
        debugMode = value;
    }

    void GraphicsContext::set_main_shader(GLShaderProgram* shader) {
        mainShader = shader;
    }

    void GraphicsContext::set_line_shader(GLShaderProgram* shader) {
        lineShader = shader;
    }

    const bool& GraphicsContext::is_debug() const {
        return debugMode;
    }

    GLShaderProgram* GraphicsContext::get_main_shader() {
        return mainShader;
    }

    GLShaderProgram* GraphicsContext::get_line_shader() {
        return lineShader;
    }
}

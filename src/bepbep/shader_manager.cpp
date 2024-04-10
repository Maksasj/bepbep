#include "shader_manager.h"

namespace bepbep {
    ShaderManager::ShaderManager() {

    }

    GLShaderProgram* ShaderManager::load_shader(const string& vertPath, const string& fragPath) {
        auto vertexShader = GLShaderFactory::create_shader(vertPath, ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
        auto fragmentShader = GLShaderFactory::create_shader(fragPath, ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);

        auto shader = new GLShaderProgram(vertexShader, fragmentShader);

        vertexShader.destroy();
        fragmentShader.destroy();

        return shader;
    }

    void ShaderManager::load() {
        shaders["flat"] = load_shader("shaders/main_vert.glsl", "shaders/main_frag.glsl");
        shaders["line"] = load_shader("shaders/line_vert.glsl", "shaders/line_frag.glsl");
    }

    const GLShaderProgram* ShaderManager::get_shader(const string& shaderName) {
        if(shaders.contains(shaderName))
            return shaders[shaderName];

        return nullptr;
    }
}

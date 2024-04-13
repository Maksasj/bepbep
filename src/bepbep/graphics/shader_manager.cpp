#include "shader_manager.h"

namespace bepbep {
    ShaderManager::ShaderManager() {

    }

    GLShaderProgram* ShaderManager::load_shader_program(const string& vertPath, const string& fragPath) {
        auto vertexShader = GLShaderFactory::create_shader(vertPath, ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
        auto fragmentShader = GLShaderFactory::create_shader(fragPath, ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);

        auto shader = new GLShaderProgram(vertexShader, fragmentShader);

        vertexShader.destroy();
        fragmentShader.destroy();

        return shader;
    }

    GLShaderProgram* ShaderManager::load_shader(const string& name, const string& vertPath, const string& fragPath) {
        auto shader = load_shader_program(vertPath, fragPath);

        shaders[name] = shader;

        return shader;
    }

    const GLShaderProgram* ShaderManager::get_shader(const string& shaderName) {
        if(shaders.contains(shaderName))
            return shaders[shaderName];

        return nullptr;
    }
}

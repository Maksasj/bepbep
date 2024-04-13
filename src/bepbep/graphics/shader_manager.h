#ifndef _BEPBEP_SHADER_MANAGER_H_
#define _BEPBEP_SHADER_MANAGER_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class ShaderManager {
        private:
            unordered_map<string, GLShaderProgram*> shaders;

            static GLShaderProgram* load_shader_program(const string& vertPath, const string& fragPath);

        public:
            ShaderManager();

            GLShaderProgram* load_shader(const string& name, const string& vertPath, const string& fragPath);

            const GLShaderProgram* get_shader(const string& shaderName);
    };
}

#endif
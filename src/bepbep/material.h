#ifndef _BEPBEP_MATERIAL_H_
#define _BEPBEP_MATERIAL_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Material {
        private:
            GLShaderProgram* shader;

        public:
            void bind() {
                shader->enable();

                // Bind all textures and floats
            }

            GLShaderProgram* get_shader() {
                return shader;
            }
    };
}

#endif
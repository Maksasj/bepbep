#ifndef _BEPBEP_IMATERIAL_H_
#define _BEPBEP_IMATERIAL_H_

#include "common/vertex.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class IMaterial {
        private:
            GLShaderProgram* shader;

        public:
            IMaterial(GLShaderProgram* sh) : shader(sh) {

            }

            virtual void bind() {
                shader->enable();
            }

            virtual void unbind() {

            }

            GLShaderProgram* get_shader() {
                return shader;
            }
    };
}

#endif
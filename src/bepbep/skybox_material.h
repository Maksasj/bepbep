#ifndef _BEPBEP_SKYBOX_MATERIAL_H_
#define _BEPBEP_SKYBOX_MATERIAL_H_

#include "imaterial.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class SkyBoxMaterial : public IMaterial {
        private:
            GLTexture* albedoMap;

        public:
            SkyBoxMaterial(GLShaderProgram* sh, GLTexture* albedo) : IMaterial(sh), albedoMap(albedo) {

            }

            void bind() override {
                glDepthFunc(GL_LEQUAL);
                glDepthMask(GL_FALSE);
                IMaterial::bind();

                if(albedoMap)
                    albedoMap->bind_texture_unit(0);
            }

            void unbind() override {
                glDepthFunc(GL_LESS);
                glDepthMask(GL_TRUE);
            }
    };
}

#endif
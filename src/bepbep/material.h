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

            GLTexture2D* albedoMap;
            GLTexture2D* aoMap;
            GLTexture2D* metallicMap;
            GLTexture2D* normalMap;
            GLTexture2D* roughnessMap;

        public:
            Material(
                GLShaderProgram* sh,
                GLTexture2D* albedo,
                GLTexture2D* ao,
                GLTexture2D* metallic,
                GLTexture2D* normal,
                GLTexture2D* roughness
            ) : shader(sh),
                albedoMap(albedo),
                aoMap(ao),
                metallicMap(metallic),
                normalMap(normal),
                roughnessMap(roughness)
            {

            }

            void bind() {
                shader->enable();

                if(albedoMap)
                    albedoMap->bind_texture_unit(0);

                if(aoMap)
                    aoMap->bind_texture_unit(1);

                if(metallicMap)
                    metallicMap->bind_texture_unit(2);

                if(normalMap)
                    normalMap->bind_texture_unit(3);

                if(roughnessMap)
                    roughnessMap->bind_texture_unit(4);
            }

            GLShaderProgram* get_shader() {
                return shader;
            }
    };
}

#endif
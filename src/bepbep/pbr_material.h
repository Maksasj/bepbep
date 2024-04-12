#ifndef _BEPBEP_PBR_MATERIAL_H_
#define _BEPBEP_PBR_MATERIAL_H_

#include "imaterial.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class PBRMaterial : public IMaterial {
        private:
            GLTexture* albedoMap;
            GLTexture* aoMap;
            GLTexture* metallicMap;
            GLTexture* normalMap;
            GLTexture* roughnessMap;
            GLTexture* environmentMap;

        public:
            PBRMaterial(
                GLShaderProgram* sh,
                GLTexture* albedo,
                GLTexture* ao,
                GLTexture* metallic,
                GLTexture* normal,
                GLTexture* roughness,
                GLTexture* environment
            ) : IMaterial(sh),
                albedoMap(albedo),
                aoMap(ao),
                metallicMap(metallic),
                normalMap(normal),
                roughnessMap(roughness),
                environmentMap(environment)
            {

            }

            void bind() {
                IMaterial::bind();

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

                if(environmentMap)
                    environmentMap->bind_texture_unit(5);
            }
    };
}

#endif
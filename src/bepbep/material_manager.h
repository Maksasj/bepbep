#ifndef _BEPBEP_MATERIAL_MANAGER_H_
#define _BEPBEP_MATERIAL_MANAGER_H_

#include "material.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class MaterialManager {
        private:
            unordered_map<string, Material*> materials;

        public:
            Material* create_material(
                const string& name,
                GLShaderProgram* shader,
                GLTexture2D* albedo,
                GLTexture2D* ao,
                GLTexture2D* metallic,
                GLTexture2D* normal,
                GLTexture2D* roughness)
            {
                auto* material = new Material(shader, albedo, ao, metallic, normal, roughness);

                materials[name] = material;

                return material;
            }

            Material* get_material(const string& name) {
                return materials[name];
            }

    };
}

#endif
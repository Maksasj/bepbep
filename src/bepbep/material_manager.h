#ifndef _BEPBEP_MATERIAL_MANAGER_H_
#define _BEPBEP_MATERIAL_MANAGER_H_

#include "imaterial.h"
#include "pbr_material.h"
#include "skybox_material.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class MaterialManager {
        private:
            unordered_map<string, IMaterial*> materials;

        public:
            IMaterial* create_pbr_material(
                const string& name,
                GLShaderProgram* shader,
                GLTexture* albedo,
                GLTexture* ao,
                GLTexture* metallic,
                GLTexture* normal,
                GLTexture* roughness,
                GLTexture* environment
            ) {
                IMaterial* material = new PBRMaterial(shader, albedo, ao, metallic, normal, roughness, environment);
                materials[name] = material;
                return material;
            }

            IMaterial* create_skybox_material(const string& name, GLShaderProgram* shader, GLTexture* albedo) {
                IMaterial* material = new SkyBoxMaterial(shader, albedo);
                materials[name] = material;
                return material;
            }

            IMaterial* get_material(const string& name) {
                return materials[name];
            }

    };
}

#endif
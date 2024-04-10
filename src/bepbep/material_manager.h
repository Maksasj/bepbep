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
            Material* create_material(const string& name, GLShaderProgram* shader) {
                Material* material = new Material(shader);

                materials[name] = material;

                return material;
            }

            Material* get_material(const string& name) {
                return materials[name];
            }

    };
}

#endif
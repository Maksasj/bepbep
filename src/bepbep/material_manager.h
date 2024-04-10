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
            Material* get_material(const string& name) {
                return materials[name];
            }

    };
}

#endif
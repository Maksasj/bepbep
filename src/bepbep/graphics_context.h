#ifndef _BEPBEP_GRAPHICS_CONTEXT_H_
#define _BEPBEP_GRAPHICS_CONTEXT_H_

#include "material.h"

namespace bepbep {
    class GraphicsContext {
        private:
            bool debugMode;

            Material* activeMaterial;

        public:
            GraphicsContext(const bool& debug, Material* material);

            const bool& is_debug() const;
            Material* get_active_material();

    };
}

#endif
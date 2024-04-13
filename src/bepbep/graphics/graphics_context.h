#ifndef _BEPBEP_GRAPHICS_CONTEXT_H_
#define _BEPBEP_GRAPHICS_CONTEXT_H_

#include "pbr_material.h"

namespace bepbep {
    class GraphicsContext {
        private:
            bool debugMode;

            IMaterial* activeMaterial;

        public:
            GraphicsContext(const bool& debug, IMaterial* material);

            const bool& is_debug() const;
            IMaterial* get_active_material();

    };
}

#endif
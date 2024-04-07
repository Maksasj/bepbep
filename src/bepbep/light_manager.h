#ifndef _BEPBEP_LIGHT_MANAGER_H_
#define _BEPBEP_LIGHT_MANAGER_H_

#include "graphics_context.h"
#include "light.h"
#include "vertex.h"

namespace bepbep {
    struct alignas(16) Lights {
        int lightCount;
        Light lights[16];
    };

    class LightManager {
        private:
            Light lights[16];
            int lightCount;

            unique_ptr<GLUniformBufferObject> buffer;

        public:
            LightManager();

            void load();
            void add_light(const Light& light);

            void bind(GraphicsContext& context);
            void render(GraphicsContext& context);
    };
}

#endif
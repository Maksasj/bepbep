#ifndef _BEPBEP_LIGHT_MANAGER_H_
#define _BEPBEP_LIGHT_MANAGER_H_

#include "graphics_context.h"
#include "light.h"
#include "vertex.h"

namespace bepbep {
    struct Lights {
        int lightCount;
        Light lights[16];
    };

    class LightManager {
        private:
            Light lights[16];
            int lightCount;

            unique_ptr<GLUniformBufferObject> buffer;

        public:
            LightManager() {
                buffer = make_unique<GLUniformBufferObject>(sizeof(int));

                lightCount = 0;
            }

            void add_light(const Light& light) {
                lights[lightCount] = light;
                ++lightCount;
            }

            void bind(GraphicsContext& context) {
                auto shader = context.get_main_shader();

                buffer->bind();
                shader->bind_buffer("Lights", 0, *buffer);

                auto ptr = static_cast<Lights*>(buffer->map());

                for(int i = 0; i < lightCount; ++i) {
                    ptr->lights[i] = lights[i];
                }

                ptr->lightCount = lightCount;
                buffer->unmap();

                buffer->unbind();
            }

            void render(GraphicsContext& context) {
                auto shader = context.get_line_shader();
                shader->enable();

                for(int i = 0; i < lightCount; ++i) {
                    shader->set_uniform("transform", Mat4f::translation(lights[i].origin));

                    context.render_sphere();
                }
            }
    };
}

#endif
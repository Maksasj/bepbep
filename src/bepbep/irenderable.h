#ifndef _BEPBEP_IRENDERABLE_H_
#define _BEPBEP_IRENDERABLE_H_

#include "pbr_material.h"
#include "renderer.h"

#include "graphics_context.h"

namespace bepbep {
    class IRenderable {
        private:
            Renderer* renderer;
            IMaterial* material;

        public:
            IRenderable() : renderer(nullptr), material(nullptr) {

            }

            virtual ~IRenderable() {
                // handle rendere and material deletion
            }

            void render(GraphicsContext& context, const Transform& transform) {
                renderer->render(context, transform);
            }

            void set_renderer(Renderer* value) {
                renderer = value;
            }

            void set_material(IMaterial* value) {
                material = value;
            }

            Renderer* get_renderer() {
                return renderer;
            }

            IMaterial* get_material() {
                return material;
            }
    };
}

#endif
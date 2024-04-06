#ifndef _BEPBEP_RENDERER_H_
#define _BEPBEP_RENDERER_H_

#include "graphics_context.h"
#include "mesh.h"

namespace bepbep {
    struct Object;

    using namespace bebone::core;

    struct Transform {
        Mat4f translation;
        Mat4f rotation;
    };

    class Renderer {
        private:

        public:
            virtual void render(GraphicsContext& context, const Transform& transform) = 0;
    };

    class CubeRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            CubeRenderer();

            void render(GraphicsContext& context, const Transform& transform) override;
    };

    class ChunkRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            void render(GraphicsContext& context, const Transform& transform) override;

            void swap_mesh(unique_ptr<Mesh> in) {
                mesh = std::move(in);
            }
    };

    class StructureRenderer : public Renderer {
        private:

        public:
            void render(GraphicsContext& context, const Transform& transform) override;
    };
}

#endif
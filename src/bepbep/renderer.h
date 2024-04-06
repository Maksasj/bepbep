#ifndef _BEPBEP_RENDERER_H_
#define _BEPBEP_RENDERER_H_

#include "graphics_context.h"
#include "mesh.h"

#include "transform.h"

namespace bepbep {
    using namespace bebone::core;

    struct Object;
    struct Entity;
    struct Structure;

    class Renderer {
        private:

        public:
            virtual ~Renderer() = default;
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

            void swap_mesh(unique_ptr<Mesh> in);
    };

    class StructureRenderer : public Renderer {
        private:
            Structure* structure;
        public:
            StructureRenderer(Structure* ptr);

            void render(GraphicsContext& context, const Transform& transform) override;
    };
}

#endif
#ifndef _BEPBEP_RENDERER_H_
#define _BEPBEP_RENDERER_H_

#include "mesh.h"
#include "model.h"
#include "mesh_builder.h"
#include "transform.h"

namespace bepbep {
    using namespace bebone::core;

    struct Object;
    struct Entity;
    struct Structure;

    struct GraphicsContext;

    class Renderer {
        private:

        public:
            virtual ~Renderer() = default;
            virtual void render(GraphicsContext& context, const Transform& transform) = 0;
    };

    class ModelRenderer : public Renderer {
        private:
            shared_ptr<Model> model;

        public:
            ModelRenderer(shared_ptr<Model>& m);

            void render(GraphicsContext& context, const Transform& transform) override;
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

    class IcosahedronRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            IcosahedronRenderer();

            void render(GraphicsContext& context, const Transform& transform) override;

            static vector<VertexTriangle> generate_icosahedron_triangles();
    };

    class SphereRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            SphereRenderer(const float& radius, const u32& lod);

            void render(GraphicsContext& context, const Transform& transform) override;

            static vector<VertexTriangle> generate_sphere_triangles(const float& radius, const u32& lod);
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
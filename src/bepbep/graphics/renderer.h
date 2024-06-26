#ifndef _BEPBEP_RENDERER_H_
#define _BEPBEP_RENDERER_H_

#include "graphics/pbr_material.h"
#include "graphics/mesh.h"
#include "model.h"
#include "graphics/mesh_builder.h"
#include "common/transform.h"

namespace bepbep {
    using namespace bebone::core;

    struct Object;
    struct Entity;
    struct Structure;

    struct GraphicsContext;

    class Renderer {
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

    class PlaneRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            PlaneRenderer(const f32& width, const f32& height);

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
            static void calculate_normals(vector<VertexTriangle>& triangles);
    };

    class SphereRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            SphereRenderer(const float& radius, const u32& lod);

            void render(GraphicsContext& context, const Transform& transform) override;

            static vector<VertexTriangle> generate_sphere_triangles(const float& radius, const u32& lod);
    };

    class CapsuleRenderer : public Renderer {
        private:
            unique_ptr<Mesh> mesh;

        public:
            CapsuleRenderer(const float& radius, const float& height, const u32& lod);

            void render(GraphicsContext& context, const Transform& transform) override;
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
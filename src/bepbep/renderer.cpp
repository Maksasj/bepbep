#include "renderer.h"

#include "entity.h"
#include "structure.h"
#include "graphics_context.h"

namespace bepbep {
    ModelRenderer::ModelRenderer(shared_ptr<Model>& m) {
        model = m;
    }

    void ModelRenderer::render(GraphicsContext& context, const Transform& transform) {
        auto shader = context.get_active_material()->get_shader();

        auto matrix = transform.calculate_final_transform();
        shader->set_uniform("transform", matrix);

        model->render();
    }

    CubeRenderer::CubeRenderer() {
        const vector<Vertex> vertices {
            {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}},
            {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}},
            {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}},
            {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}},
            {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}},
            {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}},
            {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}},
            {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}}
        };

        const vector<u32> indices {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            4, 5, 1, 1, 0, 4,
            3, 2, 6, 6, 7, 3
        };

        mesh = make_unique<Mesh>(vertices, indices);
    }

    void CubeRenderer::render(GraphicsContext& context, const Transform& transform) {
        auto shader = context.get_active_material()->get_shader();

        auto matrix = transform.calculate_final_transform();
        shader->set_uniform("transform", matrix);

        mesh->render();
    }

    void ChunkRenderer::render(GraphicsContext& context, const Transform& transform) {
        auto shader = context.get_active_material()->get_shader();

        auto matrix = transform.calculate_final_transform();
        shader->set_uniform("transform", matrix);

        mesh->render();

        /*
        if(context.is_debug()) {
            auto lineShader = context.get_line_shader();
            lineShader->enable();

            lineShader->set_uniform("transform", matrix);

            context.render_line({0, 0, 0}, {16, 0, 0}, ColorRGBA::WHITE);
            context.render_line({0, 0, 0}, {0, 16, 0}, ColorRGBA::WHITE);
            context.render_line({0, 0, 0}, {0, 0, 16}, ColorRGBA::WHITE);
            context.render_line({16, 0, 0}, {16, 16, 0}, ColorRGBA::WHITE);
            context.render_line({16, 0, 0}, {16, 0, 16}, ColorRGBA::WHITE);
            context.render_line({0, 16, 0}, {16, 16, 0}, ColorRGBA::WHITE);
            context.render_line({0, 16, 0}, {0, 16, 16}, ColorRGBA::WHITE);
            context.render_line({16, 16, 0}, {16, 16, 16}, ColorRGBA::WHITE);
            context.render_line({16, 16, 16}, {16, 0, 16}, ColorRGBA::WHITE);
            context.render_line({16, 16, 16}, {0, 16, 16}, ColorRGBA::WHITE);
            context.render_line({0, 0, 16}, {0, 16, 16}, ColorRGBA::WHITE);
            context.render_line({0, 0, 16}, {16, 0, 16}, ColorRGBA::WHITE);
        }
        */
    }

    void ChunkRenderer::swap_mesh(unique_ptr<Mesh> in) {
        mesh = move(in);
    }

    StructureRenderer::StructureRenderer(Structure* ptr) : structure(ptr) {

    }

    void StructureRenderer::render(GraphicsContext& context, const Transform& transform) {
        for(auto& ch : structure->get_chunks()) {
            auto& cords = ch.first;
            auto& chunk = ch.second;

            Transform newTransform = transform;
            newTransform.position.x += static_cast<f32>(cords.x) * 16.0f;
            newTransform.position.y += static_cast<f32>(cords.y) * 16.0f;
            newTransform.position.z += static_cast<f32>(cords.z) * 16.0f;

            if(chunk->renderer != nullptr)
                chunk->renderer->render(context, newTransform);
        }
    }

    IcosahedronRenderer::IcosahedronRenderer() {
        auto triangles = IcosahedronRenderer::generate_icosahedron_triangles();
        calculate_normals(triangles);

        MeshBuilder builder;
        mesh = builder.append(triangles).build();
    }

    void IcosahedronRenderer::render(GraphicsContext &context, const Transform &transform) {
        auto shader = context.get_active_material()->get_shader();

        auto matrix = transform.calculate_final_transform();
        shader->set_uniform("transform", matrix);

        mesh->render();
    }

    vector<VertexTriangle> IcosahedronRenderer::generate_icosahedron_triangles() {
        float phi = (1.0f + sqrt(5.0f)) * 0.5f; // golden ratio
        float a = 1.0f;
        float b = 1.0f / phi;

        auto v1  = Vertex{{0, b, -a},  Vec3f::zero, {1.0f, 1.0f} }; // Todo
        auto v2  = Vertex{{b, a, 0},   Vec3f::zero, {0.0f, 1.0f} }; // Todo
        auto v3  = Vertex{{-b, a, 0},  Vec3f::zero, {0.0f, 0.0f} }; // Todo
        auto v4  = Vertex{{0, b, a},   Vec3f::zero, {1.0f, 0.0f} }; // Todo
        auto v5  = Vertex{{0, -b, a},  Vec3f::zero, {1.0f, 1.0f} }; // Todo
        auto v6  = Vertex{{-a, 0, b},  Vec3f::zero, {0.0f, 1.0f} }; // Todo
        auto v7  = Vertex{{0, -b, -a}, Vec3f::zero, {0.0f, 0.0f} }; // Todo
        auto v8  = Vertex{{a, 0, -b},  Vec3f::zero, {1.0f, 0.0f} }; // Todo
        auto v9  = Vertex{{a, 0, b},   Vec3f::zero, {1.0f, 1.0f} }; // Todo
        auto v10 = Vertex{{-a, 0, -b}, Vec3f::zero, {0.0f, 1.0f} }; // Todo
        auto v11 = Vertex{{b, -a, 0},  Vec3f::zero, {0.0f, 0.0f} }; // Todo
        auto v12 = Vertex{{-b, -a, 0}, Vec3f::zero, {1.0f, 0.0f} }; // Todo

        vector<VertexTriangle> triangles = {
            {{v3, v2, v1}},
            {{v2, v3, v4}},
            {{v6, v5, v4}},
            {{v5, v9, v4}},
            {{v8, v7, v1}},
            {{v7, v10, v1}},
            {{v12, v11, v5}},
            {{v11, v12, v7}},
            {{v10, v6, v3}},
            {{v6, v10, v12}},
            {{v9, v8, v2}},
            {{v8, v9, v11}},
            {{v3, v6, v4}},
            {{v9, v2, v4}},
            {{v10, v3, v1}},
            {{v2, v8, v1}},
            {{v12, v10, v7}},
            {{v8, v11, v7}},
            {{v6, v12, v5}},
            {{v11, v9, v5}},
        };

        return triangles;
    }

    void IcosahedronRenderer::calculate_normals(vector<VertexTriangle>& triangles) {
        for(auto& tri : triangles) {
            const auto a = tri.v[0].pos - tri.v[1].pos;
            const auto b = tri.v[1].pos - tri.v[2].pos;

            const auto normal = a.cross(b).normalize();

            for(auto& v : tri.v)
                v.normal = normal;
        }
    }

    SphereRenderer::SphereRenderer(const float& radius, const u32& lod) {
        auto triangles = SphereRenderer::generate_sphere_triangles(radius, lod);
        IcosahedronRenderer::calculate_normals(triangles);

        MeshBuilder builder;
        mesh = builder.append(triangles).build();
    }

    void SphereRenderer::render(GraphicsContext &context, const Transform &transform) {
        auto shader = context.get_active_material()->get_shader();

        auto matrix = transform.calculate_final_transform();
        shader->set_uniform("transform", matrix);

        mesh->render();
    }

    vector<VertexTriangle> SphereRenderer::generate_sphere_triangles(const float& radius, const u32& lod) {
        auto triangles = IcosahedronRenderer::generate_icosahedron_triangles();

        for(u32 l = 0; l < lod; ++l) {
            vector<VertexTriangle> tmp;

            for(auto& tri : triangles) {
                auto res = tri.subdivide();

                for(auto& r : res)
                    r.project_to_unit_sphere(radius);

                tmp.insert(tmp.end(), res.begin(), res.end());
            }

            triangles = tmp;
        }

        return triangles;
    }

    CapsuleRenderer::CapsuleRenderer(const float& radius, const float& height, const u32& lod) {
        auto triangles = SphereRenderer::generate_sphere_triangles(radius, lod);

        for(auto& tri : triangles) {
            for(auto& v : tri.v) {
                if(v.pos.y < 0)
                    v.pos.y -= height;
                else if(v.pos.y > 0)
                    v.pos.y += height;
            }
        }

        IcosahedronRenderer::calculate_normals(triangles);

        MeshBuilder builder;
        mesh = builder.append(triangles).build();
    }

    void CapsuleRenderer::render(GraphicsContext& context, const Transform& transform) {
        auto shader = context.get_active_material()->get_shader();

        auto matrix = transform.calculate_final_transform();
        shader->set_uniform("transform", matrix);

        mesh->render();
    }
}

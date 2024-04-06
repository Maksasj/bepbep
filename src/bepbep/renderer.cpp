#include "renderer.h"

#include "entity.h"
#include "structure.h"
#include "graphics_context.h"

namespace bepbep {
    CubeRenderer::CubeRenderer() {
        const std::vector<Vertex> vertices {
            {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}},
            {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}},
            {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}},
            {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}},
            {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}},
            {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}},
            {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}},
            {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}}
        };

        const std::vector<u32> indices {
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
        auto mainShader = context.get_main_shader();

        mainShader->enable();
        mainShader->set_uniform("transform", transform.calculate_final_transform());

        mesh->render();
    }

    void ChunkRenderer::render(GraphicsContext& context, const Transform& transform) {
        auto mainShader = context.get_main_shader();

        auto matrix = transform.calculate_final_transform();

        mainShader->enable();
        mainShader->set_uniform("transform", matrix);

        mesh->render();

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
    }

    void ChunkRenderer::swap_mesh(unique_ptr<Mesh> in) {
        mesh = std::move(in);
    }

    StructureRenderer::StructureRenderer(Structure* ptr) : structure(ptr) {

    }

    void StructureRenderer::render(GraphicsContext& context, const Transform& transform) {
        for(auto& ch : structure->get_chunks()) {
            if(ch->renderer != nullptr)
                ch->renderer->render(context, transform);
        }
    }

    IcosahedronRenderer::IcosahedronRenderer() {
        auto triangles = IcosahedronRenderer::generate_icosahedron_triangles();

        MeshBuilder builder;

        mesh = builder.append(triangles).build();
    }

    void IcosahedronRenderer::render(GraphicsContext &context, const Transform &transform) {
        auto mainShader = context.get_main_shader();

        auto matrix = transform.calculate_final_transform();

        mainShader->enable();
        mainShader->set_uniform("transform", matrix);

        mesh->render();
    }

    std::vector<VertexTriangle> IcosahedronRenderer::generate_icosahedron_triangles() {
        float phi = (1.0f + sqrt(5.0f)) * 0.5f; // golden ratio
        float a = 1.0f;
        float b = 1.0f / phi;

        auto v1  = Vertex{{0, b, -a}, ColorRGBA::BLACK };
        auto v2  = Vertex{{b, a, 0}, ColorRGBA::WHITE };
        auto v3  = Vertex{{-b, a, 0}, ColorRGBA::RED };
        auto v4  = Vertex{{0, b, a}, ColorRGBA::BLUE };
        auto v5  = Vertex{{0, -b, a}, ColorRGBA::GREEN };
        auto v6  = Vertex{{-a, 0, b}, ColorRGBA::YELLOW };
        auto v7  = Vertex{{0, -b, -a}, ColorRGBA::MAGENTA };
        auto v8  = Vertex{{a, 0, -b}, ColorRGBA::CYAN };
        auto v9  = Vertex{{a, 0, b}, ColorRGBA::BLACK };
        auto v10 = Vertex{{-a, 0, -b}, ColorRGBA::WHITE };
        auto v11 = Vertex{{b, -a, 0}, ColorRGBA::RED };
        auto v12 = Vertex{{-b, -a, 0}, ColorRGBA::BLUE };

        return {
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
    }

    SphereRenderer::SphereRenderer(const float& radius, const u32& lod) {
        auto triangles = SphereRenderer::generate_sphere_triangles(radius, lod);

        MeshBuilder builder;
        mesh = builder.append(triangles).build();
    }

    void SphereRenderer::render(GraphicsContext &context, const Transform &transform) {
        auto mainShader = context.get_main_shader();

        auto matrix = transform.calculate_final_transform();

        mainShader->enable();
        mainShader->set_uniform("transform", matrix);

        mesh->render();
    }

    std::vector<VertexTriangle> SphereRenderer::generate_sphere_triangles(const float& radius, const u32& lod) {
        auto triangles = IcosahedronRenderer::generate_icosahedron_triangles();

        for(u32 l = 0; l < lod; ++l) {
            std::vector<VertexTriangle> tmp;

            for(auto& tri : triangles) {
                auto res = tri.subdivide();

                for(auto& r : res) {
                    r.project_to_unit_sphere(radius);
                }

                tmp.insert(tmp.end(), res.begin(), res.end());
            }

            triangles = tmp;
        }

        return triangles;
    }
}

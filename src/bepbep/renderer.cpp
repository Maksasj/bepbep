#include "renderer.h"

#include "entity.h"
#include "structure.h"

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
}

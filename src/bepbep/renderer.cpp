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
        auto shader = context.get_main_shader();

        shader->enable();
        shader->set_uniform("translation", transform.translation);
        shader->set_uniform("rotation", transform.rotation);

        mesh->render();
    }

    void ChunkRenderer::render(GraphicsContext& context, const Transform& transform) {
        auto mainShader = context.get_main_shader();
        mainShader->enable();

        mainShader->set_uniform("translation", transform.translation);
        mainShader->set_uniform("rotation", transform.rotation);

        mesh->render();

        /*
        if(context.is_debug()) {
            auto lineShader = context.get_line_shader();
            lineShader->enable();

            lineShader->set_uniform("translation", transform.translation);
            lineShader->set_uniform("rotation", transform.rotation);

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

    void StructureRenderer::render(GraphicsContext& context, const Transform& transform) {
        // auto structure = (Structure*) object;
        // for(auto& ch : structure->get_chunks()) {


            // if(ch->renderer != nullptr)
            //     ch->renderer->render(context, object);
        // }
    }
}

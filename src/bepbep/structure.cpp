#include "structure.h"

namespace bepbep {
    Chunk::Chunk() {
        std::memset(tiles, 0, 16 * 16);

        build_mesh();
    }

    void Chunk::build_mesh() {
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

     void Chunk::render(GraphicsContext& context) {
        auto shader = context.get_main_shader();

        if(shader != nullptr) {
            shader->enable();
            shader->set_uniform("translation", transform.translation);
            shader->set_uniform("rotation", transform.rotation);

            mesh->render();
        }

        if(context.is_debug()) {
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

    Structure::Structure() {
        chunks.push_back(std::make_unique<Chunk>());
    }

    void Structure::render(GraphicsContext& context) {
        for(auto& ch : chunks)
            ch->render(context);
    }
}

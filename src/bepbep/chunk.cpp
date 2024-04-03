#include "structure.h"

namespace bepbep {
    Chunk::Chunk() {
        std::memset(tiles, 0, 16 * 16 * 16);

        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    int v = rand() % 16;

                    if (v < 1)
                        tiles[x][y][z] = 1;
                }
            }
        }

        build_mesh();
    }

    void Chunk::build_mesh() {
        const std::vector<Vertex> vertices {
            {{ 0,    0,     1.0}, ColorRGBA::MAGENTA },
            {{ 1.0,  0,     1.0}, ColorRGBA::MAGENTA },
            {{ 1.0,  1.0,   1.0}, ColorRGBA::MAGENTA },
            {{ 0,    1.0,   1.0}, ColorRGBA::MAGENTA },
            {{ 0,    0,     0},   ColorRGBA::MAGENTA },
            {{ 1.0,  0,     0},   ColorRGBA::MAGENTA },
            {{ 1.0,  1.0,   0},   ColorRGBA::MAGENTA },
            {{ 0,    1.0,   0},   ColorRGBA::MAGENTA }
        };

        const std::vector<u32> indices {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            4, 5, 1, 1, 0, 4,
            3, 2, 6, 6, 7, 3
        };

        MeshBuilder builder;

        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    if(tiles[x][y][z] == 1) {
                        builder.append(vertices, indices, {x, y, z});
                    }
                }
            }
        }

        mesh = builder.build();
    }

     void Chunk::render(const Transform& transform, GraphicsContext& context) {
        auto mainShader = context.get_main_shader();
        mainShader->enable();

        mainShader->set_uniform("translation", transform.translation);
        mainShader->set_uniform("rotation", transform.rotation);

        mesh->render();

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
    }
}

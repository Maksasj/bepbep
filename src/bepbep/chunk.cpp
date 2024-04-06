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

        renderer = new ChunkRenderer();

        build_mesh();
    }

    void Chunk::build_mesh() {
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
                        auto color = ColorRGBA{
                            (rand() % 254 / 255.0f),
                            (rand() % 254 / 255.0f),
                            (rand() % 254 / 255.0f),
                            1.0f
                        };

                        const std::vector<Vertex> vertices {
                                {{ 0,    0,     1.0}, color },
                                {{ 1.0,  0,     1.0}, color },
                                {{ 1.0,  1.0,   1.0}, color },
                                {{ 0,    1.0,   1.0}, color },
                                {{ 0,    0,     0},   color },
                                {{ 1.0,  0,     0},   color },
                                {{ 1.0,  1.0,   0},   color },
                                {{ 0,    1.0,   0},   color }
                        };

                        builder.append(vertices, indices, {x, y, z});
                    }
                }
            }
        }

        ((ChunkRenderer*) renderer)->swap_mesh(builder.build());
    }
}

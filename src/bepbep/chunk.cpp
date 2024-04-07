#include "structure.h"

namespace bepbep {
    Chunk::Chunk() {
        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    int v = rand() % 16;

                    if (v < 1)
                        blocks[x][y][z] = new Block();
                    else
                        blocks[x][y][z] = nullptr;
                }
            }
        }

        renderer = new ChunkRenderer();

        build_mesh();
    }

    void Chunk::build_mesh() {
        const vector<u32> indices {
            0, 2, 3,
            0, 3, 1,

            4, 6, 7,
            4, 7, 5,

            8, 10, 11,
            8, 11, 9,

            12, 14, 15,
            12, 15, 13,

            16, 18, 19,
            16, 19, 17,

            20, 22, 23,
            20, 23, 21
        };

        MeshBuilder builder;

        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    if(blocks[x][y][z] != nullptr) {
                        auto color = ColorRGBA{
                            (rand() % 254 / 255.0f),
                            (rand() % 254 / 255.0f),
                            (rand() % 254 / 255.0f),
                            1.0f
                        };

                        const vector<Vertex> vertices = {

                            {{0.0f, 0.0f, 0.0f}, { 0 , 0, -1}, color},
                            {{1.0f, 0.0f, 0.0f}, { 0 , 0, -1}, color},
                            {{0.0f, 1.0f, 0.0f}, { 0 , 0, -1}, color},
                            {{1.0f, 1.0f, 0.0f}, { 0 , 0, -1}, color},

                            {{1.0f, 0.0f, 1.0f}, { 0, 0, 1 }, color},
                            {{0.0f, 0.0f, 1.0f}, { 0, 0, 1 }, color},
                            {{1.0f, 1.0f, 1.0f}, { 0, 0, 1 }, color},
                            {{0.0f, 1.0f, 1.0f}, { 0, 0, 1 },  color},

                            {{0.0f, 0.0f, 1.0f}, { -1 , 0, 0},  color},
                            {{0.0f, 0.0f, 0.0f}, { -1 , 0, 0},  color},
                            {{0.0f, 1.0f, 1.0f}, { -1 , 0, 0},  color},
                            {{0.0f, 1.0f, 0.0f}, { -1 , 0, 0},  color},

                            {{1.0f, 0.0f, 0.0f}, { 1, 0, 0 }, color},
                            {{1.0f, 0.0f, 1.0f}, { 1, 0, 0 }, color},
                            {{1.0f, 1.0f, 0.0f}, { 1, 0, 0 }, color},
                            {{1.0f, 1.0f, 1.0f}, { 1, 0, 0 }, color},

                            // Up
                            {{0.0f, 1.0f, 0.0f}, { 0 , 1, 0 },  color},
                            {{1.0f, 1.0f, 0.0f}, { 0 , 1, 0 },  color},
                            {{0.0f, 1.0f, 1.0f}, { 0 , 1, 0 },  color},
                            {{1.0f, 1.0f, 1.0f}, { 0 , 1, 0 }, color},

                            // Bottom
                            {{0.0f, 0.0f, 1.0f}, { 0 , -1, 0 },color},
                            {{1.0f, 0.0f, 1.0f}, { 0 , -1, 0 },color},
                            {{0.0f, 0.0f, 0.0f}, { 0 , -1, 0 },color},
                            {{1.0f, 0.0f, 0.0f}, { 0 , -1, 0 }, color}
                        };

                        builder.append(vertices, indices, {x, y, z});
                    }
                }
            }
        }

        ((ChunkRenderer*) renderer)->swap_mesh(builder.build());
    }
}

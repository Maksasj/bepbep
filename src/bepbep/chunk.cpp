#include "structure.h"

namespace bepbep {
    Chunk::Chunk() {
        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    int v = rand() % 16;

                    if (v < 1)
                        blocks[x][y][z] = new StoneBlock({x, y, z});
                    else
                        blocks[x][y][z] = nullptr;
                }
            }
        }

        renderer = new ChunkRenderer();

        build_mesh();
    }

    void Chunk::build_mesh() {
        MeshBuilder builder;

        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    auto block = blocks[x][y][z];

                    if(block == nullptr)
                        continue;

                    block->append_mesh(this, builder);
                }
            }
        }

        renderer->swap_mesh(builder.build());
    }
}

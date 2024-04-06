#ifndef _BEPBEP_CHUNK_H_
#define _BEPBEP_CHUNK_H_

#include "object.h"
#include "mesh_builder.h"

namespace bepbep {
    using namespace bebone::core;

    class Block {
        private:

        public:
    };

    class Chunk {
        private:
            Block* blocks[16][16][16];

        protected:
            ChunkRenderer* renderer;

            friend class Structure;
            friend class StructureRenderer;

        public:
            Chunk();

            void build_mesh();

            Block* get_block(const u32& x, const u32& y, const u32& z) {
                return blocks[x][y][z];
            }
    };
}

#endif
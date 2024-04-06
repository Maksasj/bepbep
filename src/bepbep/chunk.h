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
    };
}

#endif
#ifndef _BEPBEP_BLOCK_H_
#define _BEPBEP_BLOCK_H_

#include "object.h"
#include "graphics/mesh_builder.h"

namespace bepbep {
    using namespace bebone::core;

    class Chunk;

    class Block {
        private:

        protected:
            const Vec3i chunkPos;

        public:
            Block(const Vec3i& pos);

            virtual void append_mesh(Chunk* chunk, MeshBuilder& builder) = 0;
    };

    class StoneBlock : public Block {
        private:

        public:
            StoneBlock(const Vec3i& pos);

            void append_mesh(Chunk* chunk, MeshBuilder& builder) override;
    };
}

#endif
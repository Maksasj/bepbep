#ifndef _BEPBEP_CHUNK_H_
#define _BEPBEP_CHUNK_H_

#include "object.h"
#include "mesh_builder.h"

namespace bepbep {
    using namespace bebone::core;

    class Chunk {
        private:
            i32 tiles[16][16][16];

            std::unique_ptr<Mesh> mesh;

        public:
            Chunk();

            void build_mesh();

            void render(const Transform& transform, GraphicsContext& context);
    };
}

#endif
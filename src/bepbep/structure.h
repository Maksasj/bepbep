#ifndef _BEPBEP_STRUCTURE_H_
#define _BEPBEP_STRUCTURE_H_

#include "object.h"
#include "mesh_builder.h"

namespace bepbep {
    using namespace bebone::core;

    class Chunk : public Object {
        private:
            i32 tiles[16][16][16];

            std::unique_ptr<Mesh> mesh;

        public:
            Chunk();

            void build_mesh();

            void render(GraphicsContext& context) override;
    };

    class Structure : public Object {
        private:
            std::vector<std::unique_ptr<Chunk>> chunks;

        public:
            Structure();

            void render(GraphicsContext& context) override;
    };
}

#endif
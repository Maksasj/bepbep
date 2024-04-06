#ifndef _BEPBEP_STRUCTURE_H_
#define _BEPBEP_STRUCTURE_H_

#include "ray.h"
#include "chunk.h"
#include "object.h"
#include "mesh_builder.h"

namespace bepbep {
    using namespace bebone::core;

    class Structure : public Object {
        private:
            std::vector<std::unique_ptr<Chunk>> chunks;

        public:
            Structure(const Vec3f& pos, const float& mass);

            // void render(GraphicsContext& context) override;

            std::vector<std::unique_ptr<Chunk>>& get_chunks();
    };
}

#endif
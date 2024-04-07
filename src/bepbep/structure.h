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
            unordered_map<Vec3i, Chunk*> chunks;

        public:
            Structure(const Vec3f& pos, const float& mass);

            unordered_map<Vec3i, Chunk*>& get_chunks();
    };
}

#endif
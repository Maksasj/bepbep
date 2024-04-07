#include "structure.h"

namespace bepbep {
    Structure::Structure(const Vec3f& pos, const float& m) : Object() {
        chunks[{0, 0, 0}] = new Chunk();
        chunks[{1, 0, 0}] = new Chunk();
        chunks[{-1, 0, 0}] = new Chunk();

        transform.position = pos;
        mass = m;

        collider = new SphereCollider({8, 8, 8}, 8);
        renderer = new StructureRenderer(this);
        // renderer = new SphereRenderer(8, 2);
    }

    unordered_map<Vec3i, Chunk*>& Structure::get_chunks() {
        return chunks;
    }
}

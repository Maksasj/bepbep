#include "structure.h"

namespace bepbep {
    Structure::Structure(const Vec3f& pos, const float& m) : Object() {
        chunks.push_back(std::make_unique<Chunk>());

        transform.position = pos;
        mass = m;

        collider = new SphereCollider({8, 8, 8}, 8);
        renderer = new StructureRenderer(this);
    }

    std::vector<std::unique_ptr<Chunk>>& Structure::get_chunks() {
        return chunks;
    }
}

#include "structure.h"

namespace bepbep {
    Structure::Structure(const Vec3f& pos, const float& m) : Object() {
        chunks.push_back(std::make_unique<Chunk>());

        position = pos;
        mass = m;

        collider = new SphereCollider({8, 8, 8}, 8);
        renderer = new StructureRenderer();
    }

    /*
    void Structure::render(GraphicsContext& context) {
        Transform transform = {
            .translation = Mat4f::translation(position),
            .rotation = Mat4f::identity()
        };

        for(auto& ch : chunks)
            ch->render(transform, context);

        Object::render(context);
    }
    */

    std::vector<std::unique_ptr<Chunk>>& Structure::get_chunks() {
        return chunks;
    }
}

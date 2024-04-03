#include "structure.h"

namespace bepbep {
    Structure::Structure(const Vec3f& pos, const float& m) {
        chunks.push_back(std::make_unique<Chunk>());

        posCurrent = pos;
        posOld = pos;

        mass = m;
    }

    void Structure::render(GraphicsContext& context) {
        for(auto& ch : chunks)
            ch->render(transform, context);
    }
}

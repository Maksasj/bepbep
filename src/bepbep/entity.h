#ifndef _BEPBEP_ENTITY_H_
#define _BEPBEP_ENTITY_H_

#include "object.h"

namespace bepbep {
    using namespace bebone::core;

    class Entity : public Object {
        private:
            unique_ptr<Mesh> mesh;

        public:
            Entity(const Vec3f& pos, const float& m);

            void render(GraphicsContext& context) override;
    };
}

#endif
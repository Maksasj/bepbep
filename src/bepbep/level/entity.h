#ifndef _BEPBEP_ENTITY_H_
#define _BEPBEP_ENTITY_H_

#include "object.h"

namespace bepbep {
    using namespace bebone::core;

    class Entity : public Object {
        public:
            Entity(const Vec3f& pos, const float& m);
    };
}

#endif
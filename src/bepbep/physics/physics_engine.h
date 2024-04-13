#ifndef _BEPBEP_PHYSICS_ENGINE_H_
#define _BEPBEP_PHYSICS_ENGINE_H_

#include "level/level.h"

#include "level/object.h"

namespace bepbep {
    using namespace bebone::core;

    struct Collision {
        Object* a;
        Object* b;
        CollisionPoints point;
    };

    class PhysicsEngine {
        private:
            void resolve_collisions(const vector<Object*>& objects, const f64& dt);
            void apply_gravity(const vector<Object*>& objects);

    public:

            void step(Level* level, const f64& dt);
    };
}

#endif
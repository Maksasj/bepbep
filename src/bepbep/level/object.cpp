#include "object.h"

namespace bepbep {
    Object::Object() : IRenderable() {
        velocity = Vec3f::zero;
        acceleration = Vec3f::zero;

        collider = nullptr;
    }

    Object::~Object() {
        if(collider) delete collider;
    }
}

#include "object.h"

namespace bepbep {
    Object::Object() {

        velocity = Vec3f::zero;
        acceleration = Vec3f::zero;

        collider = nullptr;
        renderer = nullptr;
    }

    Object::~Object() {
        if(renderer) delete renderer;
        if(collider) delete renderer;
    }
}

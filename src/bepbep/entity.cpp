#include "entity.h"

namespace bepbep {
    Entity::Entity(const Vec3f& pos, const float& m) : Object() {
        transform.position = pos;

        mass = m;

        renderer = new CubeRenderer();
        collider = new SphereCollider(Vec3f::zero, 1);
    }
}

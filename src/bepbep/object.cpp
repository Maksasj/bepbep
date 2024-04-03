#include "object.h"

namespace bepbep {
    Object::Object() {
        transform.translation = Mat4f::translation(Vec3f::zero);
        transform.rotation = trait_bryan_angle_yxz(Vec3f::zero);

        posCurrent = Vec3f::zero;
        posOld = Vec3f::zero;
        acceleration = Vec3f::zero;
    }
}

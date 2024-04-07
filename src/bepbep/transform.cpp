#include "transform.h"

namespace bepbep {
    Mat4f Transform::calculate_final_transform() const {
        return Mat4f::translation(position) * rotation;
    }
}

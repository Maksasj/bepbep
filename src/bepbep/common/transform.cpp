#include "transform.h"

namespace bepbep {
    Mat4f Transform::calculate_final_transform() const {
        return rotation * Mat4f::translation(position);
    }
}

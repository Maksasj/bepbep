#ifndef _BEPBEP_TRANSFORM_H_
#define _BEPBEP_TRANSFORM_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone::core;

    struct Transform {
        Vec3f position;
        Mat4f rotation = Mat4f::identity();

        Mat4f calculate_final_transform() const;
    };
}

#endif
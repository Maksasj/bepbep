#ifndef _BEPBEP_VERTEX_H_
#define _BEPBEP_VERTEX_H_

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

namespace bepbep {
    using namespace bebone::core;

    struct Vertex {
        Vec3f pos;
        Vec3f color;
    };
}

#endif
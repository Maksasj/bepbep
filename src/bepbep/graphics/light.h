#ifndef _BEPBEP_LIGHT_H_
#define _BEPBEP_LIGHT_H_

#include "common/vertex.h"

namespace bepbep {
    struct alignas(16) Light {
        Vec3f origin;
        int padding;
        ColorRGBA color;
    };
}

#endif
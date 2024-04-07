#ifndef _BEPBEP_LIGHT_H_
#define _BEPBEP_LIGHT_H_

#include "vertex.h"

namespace bepbep {
    struct alignas(16) Light {
        Vec3f origin;
    };
}

#endif
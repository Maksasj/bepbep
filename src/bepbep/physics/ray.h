#ifndef _BEPBEP_RAY_H_
#define _BEPBEP_RAY_H_

#include "level/entity.h"
#include "level/structure.h"

namespace bepbep {
    class Ray {
        public:
            Ray(const Vec3f &orig, const Vec3f &dir);

            Vec3f orig, dir;
            Vec3f invdir;

            int sign[3];
    };

    class Box {
        public:
            Box(const Vec3f &vmin, const Vec3f &vmax);

            Vec3f bounds[2];

            float intersect(const Ray &r);
        };
}

#endif
#ifndef _BEPBEP_RAY_H_
#define _BEPBEP_RAY_H_

#include "entity.h"
#include "structure.h"

namespace bepbep {
    class Ray {
        public:
            Ray(const Vec3f &orig, const Vec3f &dir) : orig(orig), dir(dir) {
                invdir = {
                    1.0f / dir.x,
                    1.0f / dir.y,
                    1.0f / dir.z
                };

                sign[0] = (invdir.x < 0);
                sign[1] = (invdir.y < 0);
                sign[2] = (invdir.z < 0);
            }

            Vec3f orig, dir;
            Vec3f invdir;

            int sign[3];
    };

    class Box {
        public:
            Box(const Vec3f &vmin, const Vec3f &vmax) {
                bounds[0] = vmin;
                bounds[1] = vmax;
            }

            Vec3f bounds[2];

        float intersect(const Ray &r) {
            if(
                (r.orig.x > bounds[0].x &&  r.orig.x < bounds[1].x) &&
                (r.orig.y > bounds[0].y &&  r.orig.y < bounds[1].y) &&
                (r.orig.z > bounds[0].z &&  r.orig.z < bounds[1].z)
            ) {
                return 0.0f;
            }

            float tmin, tmax, tymin, tymax, tzmin, tzmax;

            tmin = (bounds[r.sign[0]].x - r.orig.x) * r.invdir.x;
            tmax = (bounds[1-r.sign[0]].x - r.orig.x) * r.invdir.x;
            tymin = (bounds[r.sign[1]].y - r.orig.y) * r.invdir.y;
            tymax = (bounds[1-r.sign[1]].y - r.orig.y) * r.invdir.y;

            if ((tmin > tymax) || (tymin > tmax))
                return -1.0f;

            if (tymin > tmin)
                tmin = tymin;
            if (tymax < tmax)
                tmax = tymax;

            tzmin = (bounds[r.sign[2]].z - r.orig.z) * r.invdir.z;
            tzmax = (bounds[1-r.sign[2]].z - r.orig.z) * r.invdir.z;

            if ((tmin > tzmax) || (tzmin > tmax))
                return -1.0f;

            if (tzmin > tmin)
                tmin = tzmin;
            if (tzmax < tmax)
                tmax = tzmax;

            return tmin;
        }
    };
}

#endif
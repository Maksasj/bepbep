#include "collision.h"

namespace bepbep {
    CollisionPoints find_sphere_sphere_collision_points(const SphereCollider* a, const Transform& aTr, const SphereCollider* b, const Transform& bTr) {
        Vec3f A = a->center + aTr.position;
        Vec3f B = b->center + bTr.position;

        float Ar = a->radius * 1; // 1 -> scale
        float Br = b->radius * 1; // 1 -> scale

        Vec3f AtoB = B - A;
        Vec3f BtoA = A - B;

        if (AtoB.length() > Ar + Br) {
            return CollisionPoints{
                .hasCollision = false
            };
        }

        A += AtoB.normalize() * Ar;
        B += BtoA.normalize() * Br;

        AtoB = B - A;

        return {
            A, B,
            AtoB.normalize(),
            AtoB.length(),
            true
        };
    }

    CollisionPoints find_sphere_plane_collision_points(const SphereCollider* a, const Transform& aTr, const PlaneCollider* b, const Transform& bTr) {
        Vec3f A = a->center + aTr.position;
        Vec3f N = b->plane * bTr.position;
        N.normalize();

        Vec3f P = N * b->distance + bTr.position;

        float Ar = a->radius * 1; // 1 -> scale

        float d = (A - P).dot(N);

        if (d > Ar) {
            return CollisionPoints{
                .hasCollision = false
            };
        }

        Vec3f B = A - N * d;
        A = A - N * Ar;

        return {
            A, B,
            N.normalize(),
            (B - A).length(),
            true
        };
    }
}

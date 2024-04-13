#ifndef _BEPBEP_COLLISION_H_
#define _BEPBEP_COLLISION_H_

#include "common/transform.h"
#include "common/vertex.h"

namespace bepbep {
    using namespace bebone::core;

    struct CollisionPoints {
        Vec3f A;
        Vec3f B;
        Vec3f normal;
        float depth;
        bool hasCollision;
    };

    struct Collider;
    struct SphereCollider;
    struct PlaneCollider;

    struct Collider {
        virtual CollisionPoints test_collision(
            const Transform& tr,
            const Collider* collider,
            const Transform& colliderTr) const = 0;

        virtual CollisionPoints test_collision(
            const Transform& tr,
            const SphereCollider* collider,
            const Transform& colliderTr) const = 0;

        virtual CollisionPoints test_collision(
            const Transform& tr,
            const PlaneCollider* collider,
            const Transform& colliderTr) const = 0;
    };

    CollisionPoints find_sphere_sphere_collision_points(
        const SphereCollider* a,
        const Transform& aTr,
        const SphereCollider* b,
        const Transform& bTr);

    CollisionPoints find_sphere_plane_collision_points(
        const SphereCollider* a,
        const Transform& aTr,
        const PlaneCollider* b,
        const Transform& bTr);

    struct SphereCollider : public Collider {
        Vec3f center;
        float radius;

        SphereCollider(const Vec3f& c, const float& r) {
            center = c;
            radius = r;
        }

        CollisionPoints test_collision(const Transform& tr, const Collider* collider, const Transform& colliderTr) const override {
            return collider->test_collision(colliderTr, this, tr);
        }

        CollisionPoints test_collision(const Transform& tr, const SphereCollider* collider, const Transform& colliderTr) const override {
            return find_sphere_sphere_collision_points(this, tr, collider, colliderTr);
        }

        CollisionPoints test_collision(const Transform& tr, const PlaneCollider* collider, const Transform& colliderTr) const override {
            return find_sphere_plane_collision_points(this, tr, collider, colliderTr);
        }
    };

    struct PlaneCollider : public Collider {
        Vec3f plane;
        float distance;

        CollisionPoints test_collision(const Transform& tr, const Collider* collider, const Transform& colliderTr) const override {
            return collider->test_collision(colliderTr, this, tr);
        }

        CollisionPoints test_collision(const Transform& tr, const SphereCollider* collider, const Transform& colliderTr) const override {
            return find_sphere_plane_collision_points(collider, colliderTr, this, tr);
        }

        CollisionPoints test_collision(const Transform& tr, const PlaneCollider* collider, const Transform& colliderTr) const override {
            return {};
        }
    };
}

#endif
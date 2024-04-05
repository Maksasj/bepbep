#ifndef _BEPBEP_COLLISION_H_
#define _BEPBEP_COLLISION_H_

#include "vertex.h"

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
        virtual CollisionPoints test_collision(const Vec3f& pos, const Collider* collider, const Vec3f& colliderPos) const = 0;
        virtual CollisionPoints test_collision(const Vec3f& pos, const SphereCollider* collider, const Vec3f& colliderPos) const = 0;
        virtual CollisionPoints test_collision(const Vec3f& pos, const PlaneCollider* collider, const Vec3f& colliderPos) const = 0;
    };

    CollisionPoints find_sphere_sphere_collision_points(const SphereCollider* a, const Vec3f& aPos, const SphereCollider* b, const Vec3f& bPos);
    CollisionPoints find_sphere_plane_collision_points(const SphereCollider* a, const Vec3f& aPos, const PlaneCollider* b, const Vec3f& bPos);

    struct SphereCollider : public Collider {
        Vec3f center;
        float radius;

        SphereCollider(const Vec3f& c, const float& r) {
            center = c;
            radius = r;
        }

        CollisionPoints test_collision(const Vec3f& pos, const Collider* collider, const Vec3f& colliderPos) const override {
            return collider->test_collision(colliderPos, this, pos);
        }

        CollisionPoints test_collision(const Vec3f& pos, const SphereCollider* collider, const Vec3f& colliderPos) const override {
            return find_sphere_sphere_collision_points(this, pos, collider, colliderPos);
        }

        CollisionPoints test_collision(const Vec3f& pos, const PlaneCollider* collider, const Vec3f& colliderPos) const override {
            return find_sphere_plane_collision_points(this, pos, collider, colliderPos);
        }
    };

    struct PlaneCollider : public Collider {
        Vec3f plane;
        float distance;

        CollisionPoints test_collision(const Vec3f& pos, const Collider* collider, const Vec3f& colliderPos) const override {
            return collider->test_collision(colliderPos, this, pos);
        }

        CollisionPoints test_collision(const Vec3f& pos, const SphereCollider* collider, const Vec3f& colliderPos) const override {
            return find_sphere_plane_collision_points(collider, colliderPos, this, pos);
        }

        CollisionPoints test_collision(const Vec3f& pos, const PlaneCollider* collider, const Vec3f& colliderPos) const override {
            return {};
        }
    };
}

#endif
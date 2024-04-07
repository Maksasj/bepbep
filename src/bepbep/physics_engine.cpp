#include "physics_engine.h"

namespace bepbep {
    void PhysicsEngine::step(Level* level, const f64& dt) {
        vector<Object*>& objects = level->get_objects();

        resolve_collisions(objects, dt);

        // apply_gravity();
        // Todo there we can iterate only neede objects
        for(auto& obj : objects) {
            obj->velocity += obj->acceleration / obj->mass * dt;
            obj->transform.position += obj->velocity * dt;

            obj->acceleration = Vec3f::zero;
        }
    }

    void PhysicsEngine::resolve_collisions(const vector<Object*>& objects, const f64& dt) {
        vector<Collision> collisions;

        for(Object* a : objects) {
            for(Object* b : objects) {
                if(a == b) break;

                if(!a->collider || !b->collider) continue;

                CollisionPoints points = a->collider->test_collision(a->transform, b->collider, b->transform);

                if(points.hasCollision) {
                    collisions.emplace_back(a, b, points);
                }
            }
        }

        for(auto& col : collisions) {
            Vec3f ab = col.point.A - col.point.B;
            Vec3f ba = col.point.B - col.point.A;

            col.a->velocity += ab;
            col.b->velocity += ba;
        }
    }

    void PhysicsEngine::apply_gravity(const vector<Object*>& objects) {
        for(auto& planet : objects) {
            for(auto& sputnik : objects) {
                if(planet == sputnik)
                    continue;

                auto vec = planet->transform.position - sputnik->transform.position;
                auto dist = vec.length();
                auto normal = vec.normalize();

                auto g = (normal * 0.8 * planet->mass) / (dist * dist);

                sputnik->acceleration += g;
            }
        }
    }
}


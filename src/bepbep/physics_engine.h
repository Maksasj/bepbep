#ifndef _BEPBEP_PHYSICS_ENGINE_H_
#define _BEPBEP_PHYSICS_ENGINE_H_

#include "object.h"

namespace bepbep {
    using namespace bebone::core;

    struct Collision {
        Object* a;
        Object* b;
        CollisionPoints point;
    };

    class PhysicsEngine {
        protected:
            std::vector<Object*> objects;

        public:
            void add_object(Object* object) {
                objects.push_back(object);
            }

            void resolve_collisions(float dt) {
                std::vector<Collision> collisions;

                for(Object* a : objects) {
                    for(Object* b : objects) {
                        if(a == b) break;

                        if(!a->collider || !b->collider) continue;

                        CollisionPoints points = a->collider->test_collision(a->position, b->collider, b->position);

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

            void applyGravity() {
                for(auto& planet : objects) {
                    for(auto& sputnik : objects) {
                        if(planet == sputnik)
                            continue;

                        auto vec = planet->position - sputnik->position;
                        auto dist = vec.length();
                        auto normal = vec.normalize();

                        auto g = (normal * 0.8 * planet->mass) / (dist * dist);

                        sputnik->acceleration += g;
                    }
                }
            }

            void step(float dt) {
                resolve_collisions(dt);

                applyGravity();

                for(auto& obj : objects) {
                    obj->velocity += obj->acceleration / obj->mass * dt;
                    obj->position += obj->velocity * dt;

                    obj->acceleration = Vec3f::zero;
                }

            }
    };
}

#endif
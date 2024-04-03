#ifndef _BEPBEP_OBJECT_H_
#define _BEPBEP_OBJECT_H_

#include "mesh.h"
#include "graphics_context.h"

namespace bepbep {
    using namespace bebone::core;

    struct Transform {
        Mat4f translation;
        Mat4f rotation;
    };

    enum ObjectType {
        ENTITY,
        STRUCTURE
    };

    class Object {
        protected:
            Transform transform;
            const ObjectType type;

        public:
            Object(const ObjectType& t);

            Vec3f posCurrent;
            Vec3f posOld;
            Vec3f acceleration;

            float mass;

            void updatePos(float dt) {
                const Vec3f velocity = posCurrent - posOld;
                posOld  = posCurrent;

                posCurrent = posCurrent + velocity + acceleration * dt * dt;

                acceleration = Vec3f::zero;

                transform.translation = Mat4f::translation(posCurrent);
            }

            void accelerate(const Vec3f& acc) {
                acceleration += acc;
            }

            virtual void render(GraphicsContext& context);

            const ObjectType& get_type() const;
    };
}

#endif
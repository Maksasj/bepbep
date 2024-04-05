#ifndef _BEPBEP_OBJECT_H_
#define _BEPBEP_OBJECT_H_

#include "mesh.h"
#include "graphics_context.h"

#include "collision.h"

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
            const ObjectType type;

        public:
            Object(const ObjectType& t);

            Vec3f position;
            Vec3f velocity;
            Vec3f acceleration;
            float mass;

            Collider* collider = nullptr;

            virtual void render(GraphicsContext& context);

            const ObjectType& get_type() const;
    };
}

#endif
#ifndef _BEPBEP_OBJECT_H_
#define _BEPBEP_OBJECT_H_

#include "mesh.h"
#include "graphics_context.h"

#include "collision.h"
#include "renderer.h"

namespace bepbep {
    using namespace bebone::core;

    class Object {
        public:
            Object();

            Vec3f position;
            Vec3f velocity;
            Vec3f acceleration;
            float mass;

            Collider* collider;
            Renderer* renderer;
    };
}

#endif
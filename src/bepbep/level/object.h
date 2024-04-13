#ifndef _BEPBEP_OBJECT_H_
#define _BEPBEP_OBJECT_H_

#include "graphics/mesh.h"
#include "graphics/graphics_context.h"

#include "physics/collision.h"

#include "graphics/irenderable.h"

namespace bepbep {
    using namespace bebone::core;

    class Object : public IRenderable {
        public:
            Object();
            virtual ~Object();

            Transform transform;

            // Physics
            Vec3f velocity;
            Vec3f acceleration;
            float mass;

            Collider* collider;

            // [x] Renderable intreface
            // - Rigidbody interface
            // [x] Shader manager
            // Material
            // Textures
            // Material manager
            // Auto pipeline thing
    };
}

#endif
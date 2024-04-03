#ifndef _BEPBEP_OBJECT_H_
#define _BEPBEP_OBJECT_H_

#include "mesh.h"

namespace bepbep {
    using namespace bebone::core;

    struct Transform {
        Mat4f translation;
        Mat4f rotation;
    };

    class Object {
        protected:
            Transform transform;

        public:
            Object();

            virtual void render(GLShaderProgram& program) = 0;
    };
}

#endif
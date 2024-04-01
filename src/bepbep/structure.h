#ifndef _BEPBEP_STRUCTURE_H_
#define _BEPBEP_STRUCTURE_H_

#include "mesh.h"

namespace bepbep {
    using namespace bebone::core;

    struct Transform {
        Mat4f translation;
        Mat4f rotation;
    };

    class Structure {
        private:
            Transform transform;

            unique_ptr<Mesh> mesh;

        public:
            Structure();

            void render(GLShaderProgram& program);
    };
}

#endif
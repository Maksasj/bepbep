#ifndef _BEPBEP_LINE_MESH_H_
#define _BEPBEP_LINE_MESH_H_

#include "common/vertex.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class LineMesh {
        private:
            unsigned long long vertexCount;

            unique_ptr<GLVertexArrayObject> vao;
            unique_ptr<GLVertexBufferObject> vbo;

        public:
            LineMesh(LineVertex* vertices, unsigned long long vCount);

            ~LineMesh();

            void update_vertices(LineVertex* vertices, unsigned long long vCount);

            void render() const;
    };
}

#endif
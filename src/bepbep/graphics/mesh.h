#ifndef _BEPBEP_MESH_H_
#define _BEPBEP_MESH_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Mesh {
        private:
            unsigned long long indicesCount;

            unique_ptr<GLVertexArrayObject> vao;
            unique_ptr<GLVertexBufferObject> vbo;
            unique_ptr<GLElementBufferObject> ebo;

        public:
            Mesh(const vector<Vertex>& vertices, const vector<u32>& indices);

            ~Mesh();

            void render() const;
    };
}

#endif
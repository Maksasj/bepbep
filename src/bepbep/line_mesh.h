#ifndef _BEPBEP_LINE_MESH_H_
#define _BEPBEP_LINE_MESH_H_

#include "vertex.h"

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
            LineMesh(LineVertex* vertices, unsigned long long vCount) : vertexCount(vCount) {
                vao = make_unique<GLVertexArrayObject>();
                vao->bind();

                vbo = make_unique<GLVertexBufferObject>(vertices, vCount * sizeof(LineVertex), GL_DYNAMIC_DRAW);

                vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(LineVertex), (void*) offsetof(LineVertex, pos));
                vao->link_attributes(*vbo, 1, 4, GL_FLOAT, sizeof(LineVertex), (void*) offsetof(LineVertex, color));

                vao->unbind();
                vbo->unbind();
            }

            ~LineMesh() {
                vao->destroy();
                vbo->destroy();
            }

            void update_vertices(LineVertex* vertices, unsigned long long vCount) {
                vbo->buffer_sub_data(0, vCount * sizeof(LineVertex), vertices);
            }

            void render() const {
                vao->bind();

                GLContext::draw_arrays(GL_LINES, 0, static_cast<i32>(vertexCount));
            }
    };
}

#endif
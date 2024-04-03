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
            Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : indicesCount(indices.size()) {
                vao = make_unique<GLVertexArrayObject>();
                vao->bind();

                vbo = make_unique<GLVertexBufferObject>(vertices.data(), vertices.size() * sizeof(Vertex));
                ebo = make_unique<GLElementBufferObject>(indices.data(), indices.size() * sizeof(u32));

                vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));
                vao->link_attributes(*vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, color));

                vao->unbind();
                vbo->unbind();
                ebo->unbind();
            }

            ~Mesh() {
                vao->destroy();
                vbo->destroy();
                ebo->destroy();
            }

            void render() const {
                vao->bind();

                GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indicesCount), GL_UNSIGNED_INT, nullptr);
            }
    };
}

#endif
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

            unique_ptr<GLVertexArrayObject> m_vao;
            unique_ptr<GLVertexBufferObject> m_vbo;
            unique_ptr<GLElementBufferObject> m_ebo;

        public:
            Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : indicesCount(indices.size()) {
                m_vao = make_unique<GLVertexArrayObject>();
                m_vao->bind();

                m_vbo = make_unique<GLVertexBufferObject>(vertices.data(), vertices.size() * sizeof(Vertex));
                m_ebo = make_unique<GLElementBufferObject>(indices.data(), indices.size() * sizeof(u32));

                m_vao->link_attributes(*m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));
                m_vao->link_attributes(*m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, color));

                m_vao->unbind();
                m_vbo->unbind();
                m_ebo->unbind();
            }

            ~Mesh() {
                m_vao->destroy();
                m_vbo->destroy();
                m_ebo->destroy();
            }

            void render() const {
                m_vao->bind();

                GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indicesCount), GL_UNSIGNED_INT, nullptr);
            }
    };
}

#endif
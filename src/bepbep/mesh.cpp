#include "mesh.h"

namespace bepbep {
    Mesh::Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : indicesCount(indices.size()) {
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

    Mesh::~Mesh() {
        vao->destroy();
        vbo->destroy();
        ebo->destroy();
    }

    void Mesh::render() const {
        vao->bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indicesCount), GL_UNSIGNED_INT, nullptr);
    }
}

#include "line_mesh.h"

namespace bepbep {
    LineMesh::LineMesh(LineVertex* vertices, unsigned long long vCount) : vertexCount(vCount) {
        vao = make_unique<GLVertexArrayObject>();
        vao->bind();

        vbo = make_unique<GLVertexBufferObject>(vertices, vCount * sizeof(LineVertex), GL_DYNAMIC_DRAW);

        vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(LineVertex), (void*) offsetof(LineVertex, pos));
        vao->link_attributes(*vbo, 1, 4, GL_FLOAT, sizeof(LineVertex), (void*) offsetof(LineVertex, color));

        vao->unbind();
        vbo->unbind();
    }

    LineMesh::~LineMesh() {
        vao->destroy();
        vbo->destroy();
    }

    void LineMesh::update_vertices(LineVertex* vertices, unsigned long long vCount) {
        vbo->buffer_sub_data(0, vCount * sizeof(LineVertex), vertices);
    }

    void LineMesh::render() const {
        vao->bind();

        GLContext::draw_arrays(GL_LINES, 0, static_cast<i32>(vertexCount));
    }
}

#include "mesh_builder.h"

namespace bepbep {
    MeshBuilder::MeshBuilder() : m_indexOffset(0) {

    }

    unique_ptr<Mesh> MeshBuilder::build() {
        return make_unique<Mesh>(m_vertices, m_indices);
    }
}
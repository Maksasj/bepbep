#include "mesh_builder.h"

namespace bepbep {
    MeshBuilder::MeshBuilder() : m_indexOffset(0) {

    }

    MeshBuilder& MeshBuilder::append(const std::vector<Vertex>& vertices, const std::vector<u32>& indices, const Vec3f& offset) {
        for(auto vertex : vertices) {
            vertex.pos += offset;

            m_vertices.push_back(vertex);
        }

        u32 maxIndex = 0;
        for(const auto& index : indices) {
            m_indices.push_back(index + m_indexOffset);

            if(index > maxIndex)
                maxIndex = index;
        }

        m_indexOffset += maxIndex + 1;

        return *this;
    }

    unique_ptr<Mesh> MeshBuilder::build() {
        return make_unique<Mesh>(m_vertices, m_indices);
    }
}
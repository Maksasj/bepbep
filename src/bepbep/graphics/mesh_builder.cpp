#include "mesh_builder.h"

namespace bepbep {
    MeshBuilder::MeshBuilder() : indexOffset(0) {

    }

    MeshBuilder& MeshBuilder::append(const vector<Vertex>& vert, const vector<u32>& ind, const Vec3f& offset) {
        for(auto vertex : vert) {
            vertex.pos += offset;

            vertices.push_back(vertex);
        }

        u32 maxIndex = 0;
        for(const auto& index : ind) {
            indices.push_back(index + indexOffset);

            if(index > maxIndex)
                maxIndex = index;
        }

        indexOffset += maxIndex + 1;

        return *this;
    }

    MeshBuilder& MeshBuilder::append(const vector<VertexTriangle>& triangles) {
        for(auto& tri : triangles)
            append({tri.v[0], tri.v[1], tri.v[2]}, {0, 1, 2}, Vec3f::zero);

        return *this;
    }

    unique_ptr<Mesh> MeshBuilder::build() {
        return make_unique<Mesh>(vertices, indices);
    }
}
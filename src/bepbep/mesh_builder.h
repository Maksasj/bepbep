#ifndef _BEPBEP_MESH_BUILDER_H_
#define _BEPBEP_MESH_BUILDER_H_

#include <memory>

#include "mesh.h"
#include "vertex.h"

namespace bepbep {
    class MeshBuilder {
        private:
            vector<Vertex> m_vertices;
            vector<u32> m_indices;

            u32 m_indexOffset;

        public:
            MeshBuilder();

            MeshBuilder& append(const vector<Vertex>& vertices, const vector<u32>& indices, const Vec3f& offset);
            MeshBuilder& append(const vector<VertexTriangle>& triangles);

            unique_ptr<Mesh> build();
        };
}

#endif
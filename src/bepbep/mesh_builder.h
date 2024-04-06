#ifndef _BEPBEP_MESH_BUILDER_H_
#define _BEPBEP_MESH_BUILDER_H_

#include <memory>

#include "mesh.h"
#include "vertex.h"

namespace bepbep {
    class MeshBuilder {
        private:
            std::vector<Vertex> m_vertices;
            std::vector<u32> m_indices;

            u32 m_indexOffset;

        public:
            MeshBuilder();

            MeshBuilder& append(const std::vector<Vertex>& vertices, const std::vector<u32>& indices, const Vec3f& offset);
            MeshBuilder& append(const std::vector<VertexTriangle>& triangles);

            std::unique_ptr<Mesh> build();
        };
}

#endif
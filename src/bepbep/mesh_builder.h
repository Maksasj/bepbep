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

            MeshBuilder& append(const std::vector<Vertex>& vertices, const std::vector<u32>& indices, const Vec3f& offset) {
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

            std::unique_ptr<Mesh> build();
        };
}

#endif
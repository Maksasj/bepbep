#ifndef _BEPBEP_MESH_BUILDER_H_
#define _BEPBEP_MESH_BUILDER_H_

#include <memory>

#include "mesh.h"
#include "common/vertex.h"

namespace bepbep {
    class MeshBuilder {
        private:
            vector<Vertex> vertices;
            vector<u32> indices;

            u32 indexOffset;

        public:
            MeshBuilder();

            MeshBuilder& append(const vector<Vertex>& vertices, const vector<u32>& indices, const Vec3f& offset);
            MeshBuilder& append(const vector<VertexTriangle>& triangles);

            unique_ptr<Mesh> build();
        };
}

#endif
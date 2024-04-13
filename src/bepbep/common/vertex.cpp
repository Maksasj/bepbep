#include "vertex.h"

namespace bepbep {
    using namespace bebone::core;

    void Vertex::project_to_unit_sphere(const float& radius) {
        pos = pos.normalize() * radius;
    }

    void VertexTriangle::project_to_unit_sphere(const float& radius) {
        v[0].project_to_unit_sphere(radius);
        v[1].project_to_unit_sphere(radius);
        v[2].project_to_unit_sphere(radius);
    }

    vector<VertexTriangle> VertexTriangle::subdivide() {
        Vertex ab = {(v[0].pos + v[1].pos) / 2.0f, Vec3f::zero, {
            (v[0].texCord + v[1].texCord) / 2.0f
        }};
        Vertex bc = {(v[1].pos + v[2].pos) / 2.0f, Vec3f::zero, {
            (v[1].texCord + v[2].texCord) / 2.0f
        }};
        Vertex ac = {(v[0].pos + v[2].pos) / 2.0f, Vec3f::zero, {
            (v[0].texCord + v[2].texCord) / 2.0f
        }};

        return {
            VertexTriangle{ {v[0], ab, ac} },
            VertexTriangle{ {ab, v[1], bc} },
            VertexTriangle{ {ab, bc, ac} },
            VertexTriangle{ {ac, bc, v[2]} }
        };
    }
}

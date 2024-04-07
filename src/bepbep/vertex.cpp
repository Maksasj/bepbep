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
            ColorRGBA{ (v[0].color.r + v[1].color.r) / 2, (v[0].color.g + v[1].color.g) / 2, (v[0].color.b + v[1].color.b) / 2, (v[0].color.a + v[1].color.a) / 2 }
        }};
        Vertex bc = {(v[1].pos + v[2].pos) / 2.0f, Vec3f::zero, {
            ColorRGBA{ (v[1].color.r + v[2].color.r) / 2, (v[1].color.g + v[2].color.g) / 2, (v[1].color.b + v[2].color.b) / 2, (v[1].color.a + v[2].color.a) / 2 }
        }};
        Vertex ac = {(v[0].pos + v[2].pos) / 2.0f, Vec3f::zero, {
            ColorRGBA{ (v[0].color.r + v[2].color.r) / 2, (v[0].color.g + v[2].color.g) / 2, (v[0].color.b + v[2].color.b) / 2, (v[0].color.a + v[2].color.a) / 2 }
        }};

        return {
            VertexTriangle{ {v[0], ab, ac} },
            VertexTriangle{ {ab, v[1], bc} },
            VertexTriangle{ {ab, bc, ac} },
            VertexTriangle{ {ac, bc, v[2]} }
        };
    }
}

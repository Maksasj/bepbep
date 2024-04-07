#ifndef _BEPBEP_VERTEX_H_
#define _BEPBEP_VERTEX_H_

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
// #define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

namespace bepbep {
    using namespace bebone::core;

    struct Vertex {
        Vec3f pos;
        Vec3f normal;
        ColorRGBA color;

        void project_to_unit_sphere(const float& radius) {
            pos = pos.normalize() * radius;
        }
    };

    struct LineVertex {
        Vec3f pos;
        ColorRGBA color;
    };

    struct VertexTriangle {
        Vertex v[3];

        void project_to_unit_sphere(const float& radius) {
            v[0].project_to_unit_sphere(radius);
            v[1].project_to_unit_sphere(radius);
            v[2].project_to_unit_sphere(radius);
        }

        std::vector<VertexTriangle> subdivide() {
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
    };

}

#endif
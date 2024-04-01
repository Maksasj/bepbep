#include "structure.h"

namespace bepbep {
    Structure::Structure() {
        transform.translation = Mat4f::translation(Vec3f::zero);
        transform.rotation = trait_bryan_angle_yxz(Vec3f::zero);

        const std::vector<Vertex> vertices {
            {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}},
            {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}},
            {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}},
            {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}},
            {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}},
            {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}},
            {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}},
            {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}}
        };

        const std::vector<u32> indices {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            4, 5, 1, 1, 0, 4,
            3, 2, 6, 6, 7, 3
        };

        mesh = make_unique<Mesh>(vertices, indices);
    }

    void Structure::render(GLShaderProgram& program) {
        program.set_uniform("translation", transform.translation);
        program.set_uniform("rotation", transform.rotation);

        mesh->render();
    }
}

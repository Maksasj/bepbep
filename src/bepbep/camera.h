#ifndef _BEPBEP_CAMERA_H_
#define _BEPBEP_CAMERA_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Camera : private core::NonCopyable {
        private:
            Mat4f viewMatrix;
            Mat4f projMatrix;

        private:
            f32 renderDistance;

            Vec3f position;
            Vec3f rotation;
            Vec3f direction;

        public:
            Camera(const Vec3f& position, const f32& renderDistance);

            void move(const Vec3f& dir);
            void bind(GLShaderProgram& shader);

            const f32& get_render_distance() const;
            const Vec3f& get_position() const;
            const Vec3f& get_rotation() const;
            const Vec3f& get_direction() const;

            void set_render_distance(const f32& renderDistance);
            void set_position(const Vec3f& pos);
            void set_rotation(const Vec3f& rot);
            void set_direction(const Vec3f& dir);

            void set_view_matrix(const Mat4f& mat);
            void set_proj_matrix(const Mat4f& mat);
    };
}

#endif
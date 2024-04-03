#ifndef _BEPBEP_CAMERA_H_
#define _BEPBEP_CAMERA_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Camera : private core::NonCopyable {
        private:
            i32 renderDistance;

            Vec3f position;
            Vec3f rotation;
            Vec3f direction;

            bool m_mouseLocked;

            Mat4f m_viewMatrix;
            Mat4f m_projMatrix;

            void update_position(shared_ptr<Window>& window);

            Mat4f calculate_view_matrix() const;

        public:
            Camera(const Vec3f& position, const i32& renderDistance);

            void move(const Vec3f& direction);

            void update(shared_ptr<Window>& window);
            void bind(GLShaderProgram& shader);

            const Vec3f& get_position() const;
            const Vec3f& get_direction() const;

            const i32& get_render_distance() const;
    };
}

#endif
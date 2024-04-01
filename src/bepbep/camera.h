#ifndef _BEPBEP_CAMERA_H_
#define _BEPBEP_CAMERA_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Camera : private core::NonCopyable {
        private:
            i32 m_renderDistance;

            Vec3f m_position;
            Vec3f m_rotation;
            Vec3f m_direction;

            bool m_mouseLocked;

            Mat4f m_viewMatrix;
            Mat4f m_projMatrix;

            Mat4f calculate_view_matrix() const;

        public:
            Camera(const Vec3f& position, const i32& renderDistance);

            void update(shared_ptr<Window>& window);
            void bind(GLShaderProgram& shader);

            const Vec3f& get_position() const;
            const i32& get_render_distance() const;
    };
}

#endif
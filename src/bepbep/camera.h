#ifndef _BEPBEP_CAMERA_H_
#define _BEPBEP_CAMERA_H_

#include "vertex.h"

namespace bepbep {
    using namespace bebone;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Camera : private core::NonCopyable {
        private:
            f32 renderDistance;

            Vec3f position;
            Vec3f rotation;
            Vec3f direction;

            bool mouseLocked;

            Mat4f viewMatrix;
            Mat4f projMatrix;

            void update_position(shared_ptr<Window>& window, const f64& dt);

            Mat4f calculate_view_matrix() const;

        public:
            Camera(const Vec3f& position, const f32& renderDistance);

            void move(const Vec3f& direction);

            void update(shared_ptr<Window>& window, const f64& dt);
            void bind(GLShaderProgram& shader);

            const Vec3f& get_position() const;
            const Vec3f& get_direction() const;
    };
}

#endif
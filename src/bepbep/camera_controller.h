#ifndef _BEPBEP_CAMERA_CONTROLLER_H_
#define _BEPBEP_CAMERA_CONTROLLER_H_

#include "camera.h"

namespace bepbep {
    using namespace bebone;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class CameraController {
        private:
            f32 camSpeed;
            bool mouseLocked;

            static Mat4f calculate_view_matrix(Camera* camera);
            static Mat4f look_at(const Vec3f& origin, const Vec3f& center, const Vec3f& up);

            void update_position_freecam(Camera* camera, const Vec2i& targetSize);
            void update_rotation_freecam(Camera* camera, const Vec2i& targetSize);

            void update_position_orbitcam(Camera* camera, const Vec2i& targetSize);
            void update_rotation_orbitcam(Camera* camera, const Vec2i& targetSize);

            void handle_mouse_lock(shared_ptr<Window>& window);

        public:
            CameraController();

            void update_position(Camera* camera, const Vec2i& targetSize);
            void update_rotation(Camera* camera, const Vec2i& targetSize);

            static void update_camera_matrices(Camera* camera, const Vec2i& targetSize);
    };
}

#endif
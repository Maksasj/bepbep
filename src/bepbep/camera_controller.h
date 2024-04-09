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

            void update_position_freecam(shared_ptr<Window>& window, Camera* camera);
            void update_rotation_freecam(shared_ptr<Window>& window, Camera* camera);

            void update_position_orbitcam(shared_ptr<Window>& window, Camera* camera);
            void update_rotation_orbitcam(shared_ptr<Window>& window, Camera* camera);

            void handle_mouse_lock(shared_ptr<Window>& window);

        public:
            CameraController();

            void update_position(shared_ptr<Window>& window, Camera* camera);
            void update_rotation(shared_ptr<Window>& window, Camera* camera);

            static void update_camera_matrices(shared_ptr<Window>& window, Camera* camera);
    };
}

#endif
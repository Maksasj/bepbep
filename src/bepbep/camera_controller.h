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

            static Mat4f calculate_view_matrix(Camera& camera);

        public:
            CameraController();

            void update_position(shared_ptr<Window>& window, Camera& camera);
            void update_rotation(shared_ptr<Window>& window, Camera& camera);
    };
}

#endif
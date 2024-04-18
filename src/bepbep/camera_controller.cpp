#include "camera_controller.h"
#include "bepbep.h"

namespace bepbep {
    CameraController::CameraController() : camSpeed(7.0f), mouseLocked(false) {

    }

    void CameraController::update_position_freecam(Camera* camera, const Vec2i& targetSize) {
        const auto dt = BepBepApp::get_delta_time();
        const auto direction = camera->get_direction();
        auto window = BepBepApp::get_window();

        auto movCamera = Vec3f::zero;

        if (glfwGetKey(window->get_backend(), 'W') == GLFW_PRESS)
            movCamera += Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'S') == GLFW_PRESS)
            movCamera -= Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'A') == GLFW_PRESS)
            movCamera += Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), 'D') == GLFW_PRESS)
            movCamera -= Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
            movCamera.y += 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            movCamera.y -= 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera->move(movCamera * camSpeed * dt * 3);
        else
            camera->move(movCamera * camSpeed * dt);
    }

    void CameraController::update_rotation_freecam(Camera* camera, const Vec2i& targetSize) {
        Vec3f rotation = camera->get_rotation();
        auto window = BepBepApp::get_window();
        // Todo
        const auto winCenterWidth = static_cast<f32>(window->get_width()) / 2.0f;
        const auto winCenterHeight = static_cast<f32>(window->get_height()) / 2.0f;

        handle_mouse_lock(window);

        if(mouseLocked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            f64 xPos, yPos;
            glfwGetCursorPos(window->get_backend(), &xPos, &yPos);

            const auto deltaX = floorf(winCenterWidth) - static_cast<f32>(xPos);
            const auto deltaY = floorf(winCenterHeight) - static_cast<f32>(yPos);

            rotation.x += deltaY * 0.005f;
            rotation.y -= deltaX * 0.005f; // If this is confusing just think that we rotate Y axis cause of movement mouse a long X axis, actual this make sense

            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        const Vec3f direction = {
            cos(rotation.y) * cos(rotation.x),
            sin(rotation.x),
            sin(rotation.y) * cos(rotation.x)
        };

        camera->set_rotation(rotation);
        camera->set_direction(direction);
    }

    void CameraController::update_position_orbitcam(Camera* camera, const Vec2i& targetSize) {

    }

    void CameraController::update_rotation_orbitcam(Camera* camera, const Vec2i& targetSize) {
        auto rotation = camera->get_rotation();
        auto window = BepBepApp::get_window();

        const auto winCenterWidth = static_cast<f32>(window->get_width()) / 2.0f;
        const auto winCenterHeight = static_cast<f32>(window->get_height()) / 2.0f;

        handle_mouse_lock(window);

        if(mouseLocked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            f64 xPos, yPos;
            glfwGetCursorPos(window->get_backend(), &xPos, &yPos);

            const auto deltaX = floorf(winCenterWidth) - static_cast<f32>(xPos);
            const auto deltaY = floorf(winCenterHeight) - static_cast<f32>(yPos);

            rotation.x += deltaX * 0.005f;
            rotation.z += deltaX * 0.005f;

            rotation.y += deltaY * 0.005f;

            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        const Vec3f direction = {
            7.0f * sin(rotation.x),
            7.0f,
            7.0f * cos(rotation.z)
        };

        camera->set_direction(direction);
        camera->set_rotation(rotation);
    }

    void CameraController::handle_mouse_lock(shared_ptr<Window>& window) {
        const auto winCenterWidth = static_cast<f32>(window->get_width()) / 2.0f;
        const auto winCenterHeight = static_cast<f32>(window->get_height()) / 2.0f;

        bool oldMouseLockState = mouseLocked;
        static auto buttonPressed = false;
        const auto isDebugButtonPressed = (glfwGetKey(window->get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
        mouseLocked = (isDebugButtonPressed && !buttonPressed) ? !mouseLocked : mouseLocked;
        buttonPressed = isDebugButtonPressed;

        if(oldMouseLockState != mouseLocked)
            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);
    }

    void CameraController::update_position(Camera* camera, const Vec2i& targetSize) {
        if(camera->locked()) {
            update_camera_matrices(camera, targetSize);
            return;
        }

        const auto type = camera->get_type();

        if(type == FREE_CAM)
            update_position_freecam(camera, targetSize);
        else if(type == ORBIT_CAM)
            update_position_orbitcam(camera, targetSize);

        update_camera_matrices(camera, targetSize);  // Todo fix this, to many re calculations
    }

    void CameraController::update_rotation(Camera* camera, const Vec2i& targetSize) {
        if(camera->locked()) {
            update_camera_matrices(camera, targetSize);
            return;
        }

        const auto type = camera->get_type();

        if(type == FREE_CAM)
            update_rotation_freecam(camera, targetSize);
        else if(type == ORBIT_CAM)
            update_rotation_orbitcam(camera, targetSize);

        const auto aspect = static_cast<f32>(targetSize.x) / static_cast<f32>(targetSize.y);
        update_camera_matrices(camera, targetSize); // Todo fix this, to many re calculations
    }

    Mat4f CameraController::calculate_view_matrix(Camera* camera) {
        const auto direction = camera->get_direction();
        const auto position = camera->get_position();

        return look_at(position, position + direction, Vec3f::up);
    }

    void CameraController::update_camera_matrices(Camera* camera, const Vec2i& targetSize) {
        const auto aspect = static_cast<f32>(targetSize.x) / static_cast<f32>(targetSize.y);
        auto proj = Mat4f::perspective(1.0472, aspect, 0.1f, camera->get_render_distance());
        camera->set_proj_matrix(proj);

        const auto type = camera->get_type();

        const auto position = camera->get_position();
        const auto direction = camera->get_direction();

        if(type == FREE_CAM) {
            camera->set_view_matrix(calculate_view_matrix(camera));
        } else if(type == ORBIT_CAM) {
            camera->set_view_matrix(look_at(position + direction, position, Vec3f::up));
        }
    }

    Mat4f CameraController::look_at(const Vec3f& origin, const Vec3f& center, const Vec3f& up) {
        const auto dir = center - origin;
        const auto w = dir.normalize();
        const auto u = w.cross(up).normalize();
        const auto v = w.cross(u);

        Mat4f viewMatrix = Mat4f::identity();
        viewMatrix[0 * 4 + 0] = u.x;
        viewMatrix[1 * 4 + 0] = u.y;
        viewMatrix[2 * 4 + 0] = u.z;
        viewMatrix[0 * 4 + 1] = v.x;
        viewMatrix[1 * 4 + 1] = v.y;
        viewMatrix[2 * 4 + 1] = v.z;
        viewMatrix[0 * 4 + 2] = w.x;
        viewMatrix[1 * 4 + 2] = w.y;
        viewMatrix[2 * 4 + 2] = w.z;
        viewMatrix[3 * 4 + 0] = -1.0f * (u).dot(origin);
        viewMatrix[3 * 4 + 1] = -1.0f * (v).dot(origin);
        viewMatrix[3 * 4 + 2] = -1.0f * (w).dot(origin);

        return viewMatrix;
    }

}

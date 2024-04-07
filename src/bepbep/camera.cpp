#include "camera.h"

namespace bepbep {
    Camera::Camera(const Vec3f& pos, const i32& rDistance) {
        renderDistance = rDistance;

        position = pos;
        rotation = Vec3f::zero;
        direction = Vec3f::zero;

        mouseLocked = true;

        viewMatrix = Mat4f::identity();
        projMatrix = Mat4f::identity();
    }

    Mat4f Camera::calculate_view_matrix() const {
        const static auto upVector = Vec3f::down;

        const auto w = direction.normalize();
        const auto u = w.cross(upVector).normalize();
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
        viewMatrix[3 * 4 + 0] = -1.0f * (u).dot(position);
        viewMatrix[3 * 4 + 1] = -1.0f * (v).dot(position);
        viewMatrix[3 * 4 + 2] = -1.0f * (w).dot(position);

        return viewMatrix;
    }

    void Camera::move(const Vec3f& direction) {
        position += direction;
    }

    void Camera::update_position(shared_ptr<Window>& window, float dt) {
        f32 speed = 4.0f;

        Vec3f movCamera = Vec3f::zero;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            speed *= 3.0f;

        if (glfwGetKey(window->get_backend(), 'W') == GLFW_PRESS)
            movCamera += Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'S') == GLFW_PRESS)
            movCamera -= Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'A') == GLFW_PRESS)
            movCamera -= Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), 'D') == GLFW_PRESS)
            movCamera += Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
            movCamera.y += 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            movCamera.y -= 1.0f;

        position += movCamera * speed * dt;
    }

    void Camera::update(shared_ptr<Window>& window, double dt) {
        update_position(window, dt);

        const auto winCenterWidth = static_cast<f32>(window->get_width()) / 2.0f;
        const auto winCenterHeight = static_cast<f32>(window->get_height()) / 2.0f;

        bool oldMouseLockState = mouseLocked;
        static auto buttonPressed = false;
        const auto isDebugButtonPressed = (glfwGetKey(window->get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
        mouseLocked = (isDebugButtonPressed && !buttonPressed) ? !mouseLocked : mouseLocked;
        buttonPressed = isDebugButtonPressed;

        if(oldMouseLockState != mouseLocked)
            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);

        if(mouseLocked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            f64 xPos, yPos;
            glfwGetCursorPos(window->get_backend(), &xPos, &yPos);

            const auto deltaX = floorf(winCenterWidth) - static_cast<f32>(xPos);
            const auto deltaY = floorf(winCenterHeight) - static_cast<f32>(yPos);

            rotation.x += deltaY * 0.005f;
            rotation.y += deltaX * 0.005f; // If this is confusing just think that we rotate Y axis cause of movement mouse a long X axis, actual this make sense

            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        direction.x = cos(rotation.y) * cos(rotation.x);
        direction.y = sin(rotation.x);
        direction.z = sin(rotation.y) * cos(rotation.x);

        viewMatrix = calculate_view_matrix();
        projMatrix = Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 2000.0f);
    }

    void Camera::bind(GLShaderProgram& shader) {
        shader.set_uniform("proj", projMatrix);
        shader.set_uniform("view", viewMatrix);

        // Todo
        shader.set_uniform("camPos.x", position.x);
        shader.set_uniform("camPos.y", position.y);
        shader.set_uniform("camPos.z", position.z);
    }

    const Vec3f& Camera::get_position() const {
        return position;
    }

    const Vec3f& Camera::get_direction() const {
        return direction;
    }

    const i32& Camera::get_render_distance() const {
        return renderDistance;
    }
}
#include "camera.h"

namespace bepbep {
    Camera::Camera(const Vec3f& pos, const f32& rD) {
        renderDistance = rD;

        position = pos;
        rotation = Vec3f::zero;
        direction = Vec3f::zero;

        viewMatrix = Mat4f::identity();
        projMatrix = Mat4f::identity();
    }

    void Camera::bind(GLShaderProgram& shader) {
        shader.set_uniform("proj", projMatrix);
        shader.set_uniform("view", viewMatrix);

        // Todo
        shader.set_uniform("camPos.x", position.x);
        shader.set_uniform("camPos.y", position.y);
        shader.set_uniform("camPos.z", position.z);
    }

    const f32& Camera::get_render_distance() const {
        return renderDistance;
    }
    const Vec3f& Camera::get_position() const {
        return position;
    }
    const Vec3f& Camera::get_rotation() const {
        return rotation;
    }
    const Vec3f& Camera::get_direction() const {
        return direction;
    }

    void Camera::set_render_distance(const f32& rD) {
        renderDistance = rD;
    }

    void Camera::set_position(const Vec3f& pos) {
        position = pos;
    }

    void Camera::set_rotation(const Vec3f& rot) {
        rotation = rot;
    }

    void Camera::set_direction(const Vec3f& dir) {
        direction = dir;
    }

    void Camera::set_view_matrix(const Mat4f& mat) {
        viewMatrix = mat;
    }
    void Camera::set_proj_matrix(const Mat4f& mat) {
        projMatrix = mat;
    }

    void Camera::move(const Vec3f &dir) {
        position += dir;
    }
}
#include "object.h"

namespace bepbep {
    Object::Object() {

        velocity = Vec3f::zero;
        acceleration = Vec3f::zero;

        collider = nullptr;
        renderer = nullptr;
    }

    Object::~Object() {
        if(renderer) delete renderer;
        if(collider) delete renderer;
    }

    /*
    void Object::render(GraphicsContext& context) {
        if(context.is_debug()) {
            // Normals
            auto lineShader = context.get_line_shader();
            lineShader->enable();

            Transform transform = {
                .translation = Mat4f::translation(position),
                .rotation = Mat4f::identity()
            };

            lineShader->set_uniform("translation", transform.translation);
            lineShader->set_uniform("rotation", transform.rotation);

            context.render_line({0, 0, 0}, {5, 0, 0}, ColorRGBA::RED);
            context.render_line({0, 0, 0}, {0, 5, 0}, ColorRGBA::BLUE);
            context.render_line({0, 0, 0}, {0, 0, 5}, ColorRGBA::GREEN);

            auto vector = velocity.normalize() * 5;
            context.render_line({0, 0, 0}, vector, ColorRGBA::MAGENTA);
        }
    }
    */
}

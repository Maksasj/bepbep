#include "object.h"

namespace bepbep {
    Object::Object(const ObjectType& t) : type(t) {
        transform.translation = Mat4f::translation(Vec3f::zero);
        transform.rotation = trait_bryan_angle_yxz(Vec3f::zero);

        posCurrent = Vec3f::zero;
        posOld = Vec3f::zero;
        acceleration = Vec3f::zero;
    }

    void Object::render(GraphicsContext& context) {
        if(context.is_debug()) {
            // Normals
            auto lineShader = context.get_line_shader();
            lineShader->enable();
            lineShader->set_uniform("translation", transform.translation);
            lineShader->set_uniform("rotation", transform.rotation);

            context.render_line({0, 0, 0}, {5, 0, 0}, ColorRGBA::RED);
            context.render_line({0, 0, 0}, {0, 5, 0}, ColorRGBA::BLUE);
            context.render_line({0, 0, 0}, {0, 0, 5}, ColorRGBA::GREEN);

            auto vector = (posCurrent - posOld).normalize() * 5;
            context.render_line({0, 0, 0}, vector, ColorRGBA::MAGENTA);
        }
    }

    const ObjectType& Object::get_type() const {
        return type;
    }
}

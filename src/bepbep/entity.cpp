#include "entity.h"

namespace bepbep {
    Entity::Entity(const std::string& filePath, const Vec3f& pos, const float& m) : Object() {
        transform.position = pos;

        mass = m;

        auto model = Model::load_from_obj(filePath);
        renderer = new ModelRenderer(model);

        // renderer = new CubeRenderer();
        collider = new SphereCollider(Vec3f::zero, 1);
    }
}

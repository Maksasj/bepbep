#include "level.h"

namespace bepbep {
    Level::Level() {
        auto suzanne = Model::load_from_obj("models/suzanne.obj");
        auto ak47 = Model::load_from_obj("models/ak47.obj");
        auto bunny = Model::load_from_obj("models/bunny.obj");

        {   // suzanne
            auto* entity = new Entity(Vec3f{2, 0, 0}, 1);
            entity->renderer = new ModelRenderer(suzanne);
            entity->collider = new SphereCollider(Vec3f::zero, 1);

            objects.push_back(entity);
        }

        {   // ak47
            auto* entity = new Entity(Vec3f{0, 0, 0}, 1);
            entity->renderer = new ModelRenderer(ak47);
            entity->collider = new SphereCollider(Vec3f::zero, 1);

            objects.push_back(entity);
        }

        objects.push_back(new Structure(Vec3f{-2, -17, 8}, 1));

        for(int i = 0; i < 5; ++i) {
            float a = ((i / 5.0f) * 2 * 3.14159265359);

            {   // ak47
                auto* entity = new Entity(Vec3f{sin(a) * 7, 10, cos(a) * 7}, 1);
                entity->renderer = new ModelRenderer(bunny);
                entity->collider = new SphereCollider(Vec3f::zero, 1);

                objects.push_back(entity);
            }
        }

        objects.push_back(new Player(Vec3f{0, 3, 0}, 1));
    }

    vector<Object*>& Level::get_objects() {
        return objects;
    }
}

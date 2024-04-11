#include "level.h"
#include "game_manager.h"

namespace bepbep {
    Level::Level() {
        MaterialManager& materials = GameManager::get_material_manager();

        auto suzanne = Model::load_from_obj("models/suzanne.obj");
        auto ak47 = Model::load_from_obj("models/ak47.obj");
        auto bunny = Model::load_from_obj("models/bunny.obj");

        {   // sphere
            auto* entity = new Entity(Vec3f{1, 0, 0}, 1);

            entity->set_renderer(new SphereRenderer(1, 8));
            entity->set_material(materials.get_material("metal"));

            entity->collider = new SphereCollider(Vec3f::zero, 1);

            objects.push_back(entity);
        }

        {   // suzanne
            auto* entity = new Entity(Vec3f{-2, 0, 0}, 1);

            entity->set_renderer(new ModelRenderer(suzanne));
            entity->set_material(materials.get_material("metal"));

            entity->collider = new SphereCollider(Vec3f::zero, 1);

            objects.push_back(entity);
        }

        {   // suzanne
            auto* entity = new Entity(Vec3f{-2, 0, 3}, 1);

            entity->set_renderer(new ModelRenderer(suzanne));
            entity->set_material(materials.get_material("brick"));

            entity->collider = new SphereCollider(Vec3f::zero, 1);

            objects.push_back(entity);
        }

        {   // plane
            auto* entity = new Entity(Vec3f{-12, -2, -12}, 1);

            entity->set_renderer(new PlaneRenderer(24, 24));
            entity->set_material(materials.get_material("metal"));

            objects.push_back(entity);
        }

        {   // ak47
            auto* entity = new Entity(Vec3f{0, -5, 0}, 1);
            entity->set_renderer(new ModelRenderer(ak47));
            entity->set_material(materials.get_material("whiteColor"));

            entity->collider = new SphereCollider(Vec3f::zero, 1);

            objects.push_back(entity);
        }

        for(int i = 0; i < 5; ++i) {
            float a = ((i / 5.0f) * 2 * 3.14159265359);

            {   // ak47
                auto* entity = new Entity(Vec3f{sin(a) * 7, 10, cos(a) * 7}, 1);

                entity->set_renderer(new ModelRenderer(bunny));
                entity->set_material(materials.get_material("metal"));

                entity->collider = new SphereCollider(Vec3f::zero, 1);

                objects.push_back(entity);
            }
        }

        // objects.push_back(new Player(Vec3f{0, 3, 0}, 1));
        // objects.push_back(new Structure(Vec3f{0, -17, 0}, 1));
    }

    vector<Object*>& Level::get_objects() {
        return objects;
    }
}

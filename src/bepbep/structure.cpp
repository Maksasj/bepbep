#include "structure.h"

#include "bepbep.h"

namespace bepbep {
    Structure::Structure(const Vec3f& pos, const float& m) : Object() {
        chunks[{0, 0, 0}] = new Chunk();
        chunks[{-1, 0, 0}] = new Chunk();

        transform.position = pos;
        mass = m;

        collider = new SphereCollider({8, 8, 8}, 8);


        MaterialManager& materials = GameManager::get_material_manager();

        set_material(materials.get_material("color"));
        set_renderer(new StructureRenderer(this));
    }

    unordered_map<Vec3i, Chunk*>& Structure::get_chunks() {
        return chunks;
    }
}

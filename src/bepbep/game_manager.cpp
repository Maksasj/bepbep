#include "game_manager.h"
#include "bepbep.h"

namespace bepbep {
    GameManager::GameManager()
        : level(nullptr)
    {
        graphics = make_unique<RenderingEngine>();
        physics = make_unique<PhysicsEngine>();
    }

    void GameManager::load() {
        graphics->load();

        level = new Level();

        cams.push_back(new Camera(FREE_CAM, Vec3f::zero, 2000.0f));
        cams.push_back(new Camera(ORBIT_CAM, Vec3f::zero, 2000.0f));

        activeCamera = 0;

        BepBepApp::get_window()->add_listener([&](InputKeyEvent& event) {
            if(event.action == GLFW_PRESS)
                if(event.key == GLFW_KEY_F5)
                    activeCamera = (activeCamera + 1) % cams.size();
        });

        BepBepApp::get_window()->add_listener([&](WindowSizeEvent& event) {
            graphics->handle_window_resize();
        });
    }

    void GameManager::run(const f64& dt) {
        physics->step(level, dt);

        if(cams.empty() || activeCamera >= cams.size()) {
            cout << "No active camera selected";
            return;
        }

        auto camera = cams[activeCamera];

        auto texture = graphics->get_first_pass().get_texture();
        auto targetSize = Vec2i(texture->get_width(), texture->get_height());

        cameraController.update_rotation(camera, targetSize);
        cameraController.update_position(camera, targetSize);

        graphics->render(level, camera);
        // graphics->render_cams(cams, activeCamera);
    }

    PhysicsEngine& GameManager::get_physics_engine() {
        return *BepBepApp::get_game_manager().physics;
    }

    RenderingEngine& GameManager::get_rendering_engine() {
        return *BepBepApp::get_game_manager().graphics;
    }

    ShaderManager& GameManager::get_shader_manager() {
        return BepBepApp::get_game_manager().graphics->get_shader_manager();
    }

    MaterialManager& GameManager::get_material_manager() {
        return BepBepApp::get_game_manager().graphics->get_material_manager();
    }
}

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
    }

    void GameManager::run(const f64& dt) {
        physics->step(level, dt);

        if(cams.empty() || activeCamera >= cams.size()) {
            cout << "No active camera selected";
            return;
        }

        auto camera = cams[activeCamera];

        auto window = BepBepApp::get_window();
        cameraController.update_rotation(window, camera);
        cameraController.update_position(window, camera);

        graphics->render(level, camera);
        graphics->render_cams(cams, activeCamera);
    }
}

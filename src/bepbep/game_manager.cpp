#include "game_manager.h"
#include "bepbep.h"

namespace bepbep {
    GameManager::GameManager()
        : level(nullptr),
          mainCamera(Vec3f::zero, 2000.0f)
    {
        graphics = make_unique<RenderingEngine>();
        physics = make_unique<PhysicsEngine>();
    }

    void GameManager::load() {
        graphics->load();

        level = new Level();
    }

    void GameManager::run(const f64& dt) {
        physics->step(level, dt);

        auto window = BepBepApp::get_window();
        cameraController.update_rotation(window, mainCamera);
        cameraController.update_position(window, mainCamera);

        graphics->render(level, mainCamera);
    }
}

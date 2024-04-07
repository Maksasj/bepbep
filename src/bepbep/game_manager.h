#ifndef _BEPBEP_GAME_MANAGER_H_
#define _BEPBEP_GAME_MANAGER_H_

#include "level.h"

#include "physics_engine.h"
#include "rendering_engine.h"

namespace bepbep {
    class GameManager {
        private:
            Level* level;

            RenderingEngine graphics;
            PhysicsEngine physics;

            Camera mainCamera;

        public:
            GameManager() : mainCamera(Vec3f::zero, 2000) {
                level = new Level();

            }

            void load() {
                graphics.load();
            }

            void run(const f64& dt) {
                physics.step(level, dt);

                graphics.render(level, mainCamera);
            }
    };
}

#endif
#ifndef _BEPBEP_GAME_MANAGER_H_
#define _BEPBEP_GAME_MANAGER_H_

#include "level.h"

#include "physics_engine.h"
#include "rendering_engine.h"

namespace bepbep {
    class BepBepApp;

    class GameManager {
        private:
            Level* level;

            unique_ptr<RenderingEngine> graphics;
            unique_ptr<PhysicsEngine> physics;

            Camera mainCamera;

        public:
            GameManager();

            void load();
            void run(const f64& dt);
    };
}

#endif
#ifndef _BEPBEP_GAME_MANAGER_H_
#define _BEPBEP_GAME_MANAGER_H_

#include "level/level.h"

#include "physics/physics_engine.h"
#include "graphics/rendering_engine.h"

#include "camera.h"
#include "camera_controller.h"

#include "player.h"
#include "player_controller.h"

namespace bepbep {
    class BepBepApp;

    class GameManager {
        private:
            Level* level;

            unique_ptr<RenderingEngine> graphics;
            unique_ptr<PhysicsEngine> physics;

            u32 activeCamera;
            vector<Camera*> cams;
            CameraController cameraController;

            Player* player;
            PlayerController playerController;

        public:
            GameManager();

            void load();
            void run(const f64& dt);

            static PhysicsEngine& get_physics_engine();
            static RenderingEngine& get_rendering_engine();
            static ShaderManager& get_shader_manager();
            static MaterialManager& get_material_manager();
    };
}

#endif
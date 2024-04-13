#ifndef _BEPBEP_H_
#define _BEPBEP_H_

#include "common/vertex.h"
#include "graphics/mesh.h"
#include "camera.h"
#include "level/level.h"
#include "graphics/graphics_context.h"
#include "graphics/light_manager.h"
#include "game_manager.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class BepBepApp {
        private:
            shared_ptr<Window> window;

            unique_ptr<GameManager> manager;
            f64 deltaTime;

        public:
            void preinit();
            void init();
            void load();
            void run();
            void cleanup();

            static BepBepApp& get_instance() {
                static BepBepApp instance;
                return instance;
            }

            static shared_ptr<Window>& get_window() {
                return get_instance().window;
            }

            static GameManager& get_game_manager() {
                return *get_instance().manager;
            }

            static const f64& get_delta_time() {
                return get_instance().deltaTime;
            }

            static void start() {
                BepBepApp& app = BepBepApp::get_instance();

                app.preinit();
                app.init();
                app.load();
                app.run();
                app.cleanup();
            }
    };
}

#endif
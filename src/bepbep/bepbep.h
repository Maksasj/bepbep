#ifndef _BEPBEP_H_
#define _BEPBEP_H_

#include "vertex.h"
#include "mesh.h"
#include "camera.h"
#include "level.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class BepBepApp {
        private:
            std::shared_ptr<Window> window;

            std::shared_ptr<GLShaderProgram> shader;

        public:
            void preinit();
            void init();
            void load();
            void run();
            void cleanup();
    };
}

#endif
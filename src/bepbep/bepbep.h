#ifndef _BEPBEP_H_
#define _BEPBEP_H_

#include "vertex.h"
#include "mesh.h"
#include "camera.h"
#include "level.h"
#include "graphics_context.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class BepBepApp {
        private:
            std::shared_ptr<Window> window;

            std::shared_ptr<GLShaderProgram> mainShader;
            std::shared_ptr<GLShaderProgram> lineShader;

            static std::shared_ptr<GLShaderProgram> load_shader(const std::string& vertPath, const std::string& fragPath);

        public:
            void preinit();
            void init();
            void load();
            void run();
            void cleanup();
    };
}

#endif
#ifndef _BEPBEP_RENDERING_ENGINE_H_
#define _BEPBEP_RENDERING_ENGINE_H_

#include "level.h"
#include "camera.h"
#include "light_manager.h"

namespace bepbep {
    class BepBepApp;

    class RenderingEngine {
        private:
            GraphicsContext context;

            shared_ptr<GLShaderProgram> mainShader;
            shared_ptr<GLShaderProgram> lineShader;

            LightManager light;

            static shared_ptr<GLShaderProgram> load_shader(const string& vertPath, const string& fragPath);

            void render_level(Level* level, Camera* camera);

        public:
            RenderingEngine();

            void load();

            void render(Level* level, Camera* camera);
    };
}

#endif
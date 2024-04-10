#ifndef _BEPBEP_RENDERING_ENGINE_H_
#define _BEPBEP_RENDERING_ENGINE_H_

#include "level.h"
#include "camera.h"
#include "light_manager.h"

#include "shader_manager.h"

namespace bepbep {
    class BepBepApp;

    class RenderingEngine {
        private:
            GraphicsContext context;

            shared_ptr<GLShaderProgram> mainShader;
            shared_ptr<GLShaderProgram> lineShader;

            LightManager light;

            unique_ptr<ShaderManager> shaderManager;

            void render_level(Level* level, Camera* camera);

            void render_freecam(Camera* camera);
            void render_orbitcam(Camera* camera);

        public:
            RenderingEngine();

            void load();

            void render(Level* level, Camera* camera);
            void render_cams(const vector<Camera*>& cams, const u32& activeCamera);
    };
}

#endif
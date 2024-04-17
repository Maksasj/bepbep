#ifndef _BEPBEP_RENDERING_ENGINE_H_
#define _BEPBEP_RENDERING_ENGINE_H_

#include "skybox.h"
#include "level/level.h"
#include "camera.h"
#include "light_manager.h"
#include "render_pass.h"

#include "texture_manager.h"
#include "shader_manager.h"
#include "material_manager.h"

namespace bepbep {
    class BepBepApp;

    class RenderingEngine {
        private:
            unique_ptr<TextureManager> textureManager;
            unique_ptr<LightManager> lightManager;
            unique_ptr<ShaderManager> shaderManager;
            unique_ptr<MaterialManager> materialManager;

            unique_ptr<SkyBox> skybox;

            unique_ptr<RenderPass> firstPass;

            GLShaderProgram* postProcessingShader;
            unique_ptr<Mesh> quad;

        public:
            RenderingEngine();

            void load();
            void render(Level* level, Camera* camera);

            void handle_window_resize();

            ShaderManager& get_shader_manager();
            MaterialManager& get_material_manager();
    };
}

#endif
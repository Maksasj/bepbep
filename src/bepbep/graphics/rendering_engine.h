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

#include "ui/main_dockspace.h"
#include "ui/level_view.h"

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

            unique_ptr<MainDockspaceWindow> dockspaceWindow;
            unique_ptr<LevelViewWindow> levelViewWindow;

            void render_geometry_pass(Level* level, Camera* camera);
            void render_post_processing_pass(Level* level, Camera* camera);
            void render_ui_pass(Level* level, Camera* camera);

        public:
            RenderingEngine();

            void load();
            void render(Level* level, Camera* camera);

            void handle_window_resize();
            void resize_passes(const i32& width, const i32& height);

            ShaderManager& get_shader_manager();
            MaterialManager& get_material_manager();
            RenderPass& get_first_pass();
    };
}

#endif
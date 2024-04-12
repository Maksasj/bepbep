#include "rendering_engine.h"
#include "bepbep.h"

namespace bepbep {
    RenderingEngine::RenderingEngine() {
        textureManager = make_unique<TextureManager>();
        lightManager = make_unique<LightManager>();
        shaderManager = make_unique<ShaderManager>();
        materialManager = make_unique<MaterialManager>();
    }

    void RenderingEngine::load() {
        auto brickAlbedo = textureManager->load_texture("brickAlbedo", "materials/brick/albedo.png");
        auto brickAo = textureManager->load_texture("brickAo", "materials/brick/ao.png");
        auto brickMetallic = textureManager->load_texture("brickMetallic", "materials/brick/metallic.png");
        auto brickNormal = textureManager->load_texture("brickNormal", "materials/brick/normal.png");
        auto brickRoughness = textureManager->load_texture("brickRoughness", "materials/brick/roughness.png");

        auto metalAlbedo = textureManager->load_texture("metalAlbedo", "materials/metal/albedo.png");
        auto metalMetallic = textureManager->load_texture("metalMetallic", "materials/metal/metallic.png");
        auto metalNormal = textureManager->load_texture("metalNormal", "materials/metal/normal.png");
        auto metalRoughness = textureManager->load_texture("metalRoughness", "materials/metal/roughness.png");

        auto skyboxAlbedo = textureManager->load_texture("skyboxAlbedo", {
            "skybox/right.jpg",
            "skybox/left.jpg",
            "skybox/bottom.jpg",
            "skybox/top.jpg",
            "skybox/front.jpg",
            "skybox/back.jpg"
        });

        auto pbrShader = shaderManager->load_shader("pbr", "shaders/pbr_vert.glsl", "shaders/pbr_frag.glsl");
        auto skyboxShader = shaderManager->load_shader("skybox", "shaders/skybox_vert.glsl", "shaders/skybox_frag.glsl");

        auto brick = materialManager->create_pbr_material("brick", pbrShader, brickAlbedo, brickAo, brickMetallic, brickNormal, brickRoughness, skyboxAlbedo);
        auto metal = materialManager->create_pbr_material("metal", pbrShader, metalAlbedo, nullptr, metalMetallic, metalNormal, metalRoughness, skyboxAlbedo);

        auto skyboxMaterial = materialManager->create_skybox_material("skybox", skyboxShader, skyboxAlbedo);

        lightManager->add_light({Vec3f{0, 10, -5}, 0, ColorRGBA::GREEN});
        lightManager->add_light({Vec3f{0, 10, 5},  0, ColorRGBA::RED});
        lightManager->add_light({Vec3f{5, 10, 0},  0, ColorRGBA::BLUE});
        lightManager->add_light({Vec3f{-5, 10, 0}, 0, ColorRGBA::YELLOW});
        // lightManager->add_light({Vec3f{1, 1, 1}, 1, ColorRGBA::WHITE});

        skybox = make_unique<SkyBox>(skyboxMaterial);
    }

    void RenderingEngine::render(Level* level, Camera* camera) {
        unordered_map<IMaterial*, vector<IRenderable*>> renderables;

        auto objects = level->get_objects();

        for(Object* obj : objects) {
            IRenderable* ren = (IRenderable*) obj;

            if(ren->get_material() == nullptr)
                continue;

            if(ren->get_renderer() == nullptr)
                continue;

            renderables[ren->get_material()].push_back(ren);
        }

        renderables[skybox->get_material()].push_back(skybox.get());

        for(auto const& [material, renders] : renderables) {
            material->bind();

            lightManager->bind(material->get_shader());
            camera->bind(material->get_shader());

            GraphicsContext context(true, material);

            for(auto& rend : renders) {
                auto obj = (Object*) rend;
                obj->render(context, obj->transform);
            }

            material->unbind();
        }

        // light.bind(context);
        // light.render(context);
//
        // render_level(level, camera);
    }

    /*
    void RenderingEngine::render_cams(const vector<Camera*>& cams, const u32& activeCamera) {
        for(u32 i = 0; i < cams.size(); ++i) {
            if(i == activeCamera)
                continue;

            const auto& camera = cams[i];

            const auto& type = camera->get_type();

            if(type == FREE_CAM) {
                render_freecam(camera);
            } else if(type == ORBIT_CAM) {
                render_orbitcam(camera);
            }
        }
    }

    void RenderingEngine::render_freecam(Camera* camera) {
        const auto& position = camera->get_position();
        const auto& rotation = camera->get_rotation();
        const auto& direction = camera->get_direction();

        auto lineShader = context.get_line_shader();
        lineShader->enable();

        lineShader->set_uniform("transform", Mat4f::identity());
        context.render_line(position, position + direction.normalize() * 3, ColorRGBA::MAGENTA);

        Transform transform = {
                .position = position - Vec3f::splat(0.5),
                .rotation = Mat4f::identity()
        };
        lineShader->set_uniform("transform", transform.calculate_final_transform());
        context.render_cube();
    }

    void RenderingEngine::render_orbitcam(Camera* camera) {
        const auto& position = camera->get_position();
        const auto& rotation = camera->get_rotation();
        const auto& direction = camera->get_direction();

        auto lineShader = context.get_line_shader();
        lineShader->enable();

        lineShader->set_uniform("transform", Mat4f::identity());
        context.render_line(position, position + direction, ColorRGBA::MAGENTA);

        Transform transform = {
            .position = position + direction,
            .rotation = Mat4f::identity()
        };
        lineShader->set_uniform("transform", transform.calculate_final_transform());
        context.render_cube();
    }
    */

    ShaderManager& RenderingEngine::get_shader_manager() {
        return *shaderManager;
    }

    MaterialManager& RenderingEngine::get_material_manager() {
        return *materialManager;
    }
}

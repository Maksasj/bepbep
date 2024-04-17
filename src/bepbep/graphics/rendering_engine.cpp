#include "rendering_engine.h"
#include "bepbep.h"

namespace bepbep {
    RenderingEngine::RenderingEngine() {
        textureManager = make_unique<TextureManager>();
        lightManager = make_unique<LightManager>();
        shaderManager = make_unique<ShaderManager>();
        materialManager = make_unique<MaterialManager>();

        firstPass = make_unique<RenderPass>();
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
            "skybox/top.jpg",
            "skybox/bottom.jpg",
            "skybox/front.jpg",
            "skybox/back.jpg"
        });

        auto pbrShader = shaderManager->load_shader("pbr", "shaders/pbr_vert.glsl", "shaders/pbr_frag.glsl");
        auto skyboxShader = shaderManager->load_shader("skybox", "shaders/skybox_vert.glsl", "shaders/skybox_frag.glsl");
        postProcessingShader = shaderManager->load_shader("skybox", "shaders/post_processing_vert.glsl", "shaders/post_processing_frag.glsl");

        auto brick = materialManager->create_pbr_material("brick", pbrShader, brickAlbedo, brickAo, brickMetallic, brickNormal, brickRoughness, skyboxAlbedo);
        auto metal = materialManager->create_pbr_material("metal", pbrShader, metalAlbedo, nullptr, metalMetallic, metalNormal, metalRoughness, skyboxAlbedo);
        auto skyboxMaterial = materialManager->create_skybox_material("skybox", skyboxShader, skyboxAlbedo);

        lightManager->add_light({Vec3f{0, 10, -5}, 0, ColorRGBA::GREEN});
        lightManager->add_light({Vec3f{0, 10, 5},  0, ColorRGBA::RED});
        lightManager->add_light({Vec3f{5, 10, 0},  0, ColorRGBA::BLUE});
        lightManager->add_light({Vec3f{-5, 10, 0}, 0, ColorRGBA::YELLOW});
        // lightManager->add_light({Vec3f{1, 1, 1}, 1, ColorRGBA::WHITE});

        skybox = make_unique<SkyBox>(skyboxMaterial);

        const vector<Vertex> vertices = {
            Vertex{{-1, -1, 0}, Vec3f::zero, {0, 0}},
            Vertex{{-1,  1, 0}, Vec3f::zero, {0, 1}},
            Vertex{{ 1, -1, 0}, Vec3f::zero, {1, 0}},
            Vertex{{ 1,  1, 0}, Vec3f::zero, {1, 1}}
        };

        const vector<u32> indicies = {
            0, 1, 2,
            1, 3, 2
        };

        quad = make_unique<Mesh>(vertices, indicies);
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

        firstPass->bind();
        GLContext::set_viewport(0, 0, 800, 600);
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(auto const& [material, renders] : renderables) {
            material->bind();

            lightManager->bind(material->get_shader());
            camera->bind(material->get_shader());

            GraphicsContext context(true, material);

            for(auto& rend : renders) {
                auto obj = (Object*) rend; // todo this think is specific only for objects, will not work with irenderables
                obj->render(context, obj->transform);
            }

            material->unbind();
        }

        firstPass->unbind();

        GLContext::set_viewport(0, 0, 800, 600);
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        postProcessingShader->enable();
        firstPass->bind_texture();
        quad->render();
    }

    ShaderManager& RenderingEngine::get_shader_manager() {
        return *shaderManager;
    }

    MaterialManager& RenderingEngine::get_material_manager() {
        return *materialManager;
    }
}

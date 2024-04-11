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

        auto whiteAlbedo = textureManager->load_color_texture("whiteAlbedo", ColorRGBA::WHITE);
        auto redAlbedo = textureManager->load_color_texture("redAlbedo", ColorRGBA::RED);

        auto mainShader = shaderManager->load_shader("main", "shaders/main_vert.glsl", "shaders/main_frag.glsl");
        auto pbrShader = shaderManager->load_shader("pbr", "shaders/pbr_vert.glsl", "shaders/pbr_frag.glsl");
        // auto lineShader = shaderManager->load_shader("line", "shaders/line_vert.glsl", "shaders/line_frag.glsl");
        // auto colorShader = shaderManager->load_shader("color", "shaders/color_vert.glsl", "shaders/color_frag.glsl");

        auto whiteColor = materialManager->create_material("whiteColor", mainShader, whiteAlbedo, nullptr, nullptr, nullptr, nullptr);
        auto redColor = materialManager->create_material("redColor", mainShader, redAlbedo, nullptr, nullptr, nullptr, nullptr);

        auto brick = materialManager->create_material("brick", pbrShader, brickAlbedo, brickAo, brickMetallic, brickNormal, brickRoughness);
        auto metal = materialManager->create_material("metal", pbrShader, metalAlbedo, brickAo, metalMetallic, metalNormal, metalRoughness);

        lightManager->add_light({Vec3f{0, 10, -5}, 0, ColorRGBA::GREEN});
        lightManager->add_light({Vec3f{0, 10, 5},  0, ColorRGBA::RED});
        lightManager->add_light({Vec3f{5, 10, 0},  0, ColorRGBA::BLUE});
        lightManager->add_light({Vec3f{-5, 10, 0}, 0, ColorRGBA::YELLOW});
        lightManager->add_light({Vec3f{5, 5, 5}, 1, ColorRGBA::WHITE});
    }

    void RenderingEngine::render_level(Level* level, Camera* camera) {
        /*
        auto objects = level->get_objects();

        if(context.is_debug()) {
            auto lineShader = context.get_line_shader();
            lineShader->enable();
            lineShader->set_uniform("transform", Mat4f::identity());

            context.render_line({0, 0, 0}, {5, 0, 0}, ColorRGBA::RED);
            context.render_line({0, 0, 0}, {0, 5, 0}, ColorRGBA::BLUE);
            context.render_line({0, 0, 0}, {0, 0, 5}, ColorRGBA::GREEN);

            context.render_sphere();

            Ray ray(camera->get_position(), camera->get_direction());

            for(auto& obj : objects) {
                auto* str = dynamic_cast<Structure*>(obj);

                if(!str)
                    continue;

                Box box(obj->transform.position, { obj->transform.position.x + 16, obj->transform.position.y + 16, obj->transform.position.z + 16 });

                float tmin = box.intersect(ray);
                if(tmin >= 0.0f) {
                    for(auto& p : str->get_chunks()) {
                        auto& chunk = p.second;

                        for(int x = 0; x < 16; ++x) {
                            for(int y = 0; y < 16; ++y) {
                                for (int z = 0; z < 16; ++z) {
                                    if(chunk->get_block(x, y, z) == nullptr)
                                        continue;

                                    Box bbbb(
                                        { obj->transform.position.x + x, obj->transform.position.y + y, obj->transform.position.z + z},
                                        { obj->transform.position.x + x + 1, obj->transform.position.y + y + 1, obj->transform.position.z + z + 1});

                                    auto t = bbbb.intersect(ray);

                                    if(t >= 0.0f) {
                                        Transform tr = {
                                                .position = ray.orig + ray.dir * t,
                                                .rotation = Mat4f::identity()
                                        };

                                        lineShader->set_uniform("transform", tr.calculate_final_transform());
                                        context.render_sphere();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        */
    }

    void RenderingEngine::render(Level* level, Camera* camera) {
        unordered_map<Material*, vector<IRenderable*>> renderables;

        auto objects = level->get_objects();

        for(Object* obj : objects) {
            if(obj->get_material() == nullptr)
                continue;

            if(obj->get_renderer() == nullptr)
                continue;

            renderables[obj->get_material()].push_back(obj);
        }

        for(auto const& [material, renders] : renderables) {
            material->bind();

            lightManager->bind(material->get_shader());
            camera->bind(material->get_shader());

            GraphicsContext context(true, material);

            for(auto& rend : renders) {
                Object* obj = (Object*) rend;
                obj->render(context, obj->transform);
            }
        }

        // light.bind(context);
        // light.render(context);
//
        // render_level(level, camera);
    }

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
        /*
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
        */
    }

    void RenderingEngine::render_orbitcam(Camera* camera) {
        /*
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
        */
    }

    ShaderManager& RenderingEngine::get_shader_manager() {
        return *shaderManager;
    }

    MaterialManager& RenderingEngine::get_material_manager() {
        return *materialManager;
    }
}

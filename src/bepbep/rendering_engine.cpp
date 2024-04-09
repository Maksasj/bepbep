#include "rendering_engine.h"
#include "bepbep.h"

namespace bepbep {
    shared_ptr<GLShaderProgram> RenderingEngine::load_shader(const string& vertPath, const string& fragPath) {
        auto vertexShader = GLShaderFactory::create_shader(vertPath, ShaderTypes::VERTEX_SHADER, ENABLE_UNIFORMS);
        auto fragmentShader = GLShaderFactory::create_shader(fragPath, ShaderTypes::FRAGMENT_SHADER, ENABLE_UNIFORMS);

        shared_ptr<GLShaderProgram> shader = make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        vertexShader.destroy();
        fragmentShader.destroy();

        return shader;
    }

    RenderingEngine::RenderingEngine() {
        light.add_light({Vec3f{0, 10, 0}});
    }

    void RenderingEngine::load() {
        mainShader = load_shader("shaders/main_vert.glsl", "shaders/main_frag.glsl");
        lineShader = load_shader("shaders/line_vert.glsl", "shaders/line_frag.glsl");

        context.set_debug_mode(true);
        context.set_main_shader(mainShader.get());
        context.set_line_shader(lineShader.get());

        // Todo
        context.init_line_mesh();
        context.init_circle_mesh();
        context.init_cube_mesh();

        light.load();
    }

    void RenderingEngine::render_level(Level* level, Camera* camera) {
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

        for(auto& obj : objects) {
            if(obj->renderer != nullptr)
                obj->renderer->render(context, obj->transform);
        }
    }

    void RenderingEngine::render(Level* level, Camera* camera) {
        mainShader->enable();
        camera->bind(*mainShader);

        lineShader->enable();
        camera->bind(*lineShader);

        light.bind(context);
        light.render(context);

        render_level(level, camera);
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
}

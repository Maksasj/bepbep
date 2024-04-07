#ifndef _BEPBEP_LEVEL_H_
#define _BEPBEP_LEVEL_H_

#include "entity.h"
#include "structure.h"

#include "physics_engine.h"

namespace bepbep {
    class Level {
        private:
            vector<shared_ptr<Object>> objects;

            PhysicsEngine engine;

        public:
            Level() {
                objects.push_back(make_shared<Entity>("models/suzanne.obj", Vec3f{2, 0, 0}, 1));

                objects.push_back(make_shared<Structure>(Vec3f{-2, -17, 8}, 1));

                for(int i = 0; i < 5; ++i) {
                    float a = ((i / 5.0f) * 2 * 3.14159265359);
                    
                    objects.push_back(make_shared<Entity>("models/bunny.obj", Vec3f{sin(a) * 7, 10, cos(a) * 7}, 1));
                }

                for(auto& o : objects)
                    engine.add_object(o.get());
            }

            void update(float dt) {
                engine.step(dt);
            }

            void render(Camera& camera, GraphicsContext& context) {
                if(context.is_debug()) {
                    auto lineShader = context.get_line_shader();
                    lineShader->enable();
                    lineShader->set_uniform("transform", Mat4f::identity());

                    context.render_line({0, 0, 0}, {5, 0, 0}, ColorRGBA::RED);
                    context.render_line({0, 0, 0}, {0, 5, 0}, ColorRGBA::BLUE);
                    context.render_line({0, 0, 0}, {0, 0, 5}, ColorRGBA::GREEN);

                    context.render_sphere();

                    Ray ray(camera.get_position(), camera.get_direction());

                    for(auto& obj : objects) {
                        auto* str = dynamic_cast<Structure*>(obj.get());

                        if(!str)
                            continue;

                        Box box(obj->transform.position, { obj->transform.position.x + 16, obj->transform.position.y + 16, obj->transform.position.z + 16 });

                        float tmin = box.intersect(ray);
                        if(tmin >= 0.0f) {
                            auto& chunk = ((Structure*) obj.get())->get_chunks()[0];

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

                for(auto& obj : objects) {
                    if(obj->renderer != nullptr)
                        obj->renderer->render(context, obj->transform);
                }
            }
    };
}

#endif
#ifndef _BEPBEP_LEVEL_H_
#define _BEPBEP_LEVEL_H_

#include "entity.h"
#include "structure.h"

namespace bepbep {
    class Level {
        private:
            std::vector<std::shared_ptr<Object>> objects;

        public:
            Level() {
                objects.push_back(std::make_shared<Structure>(Vec3f{24, 0, 0}, 10));

                objects.push_back(std::make_shared<Structure>(Vec3f{100, 0, 0}, 10));
                objects.push_back(std::make_shared<Structure>(Vec3f{-100, 50, 50}, 10));

                objects.push_back(std::make_shared<Entity>(Vec3f{0, 0, 0}, 10));
            }

            void update(float dt) {
                applyGravity();
                updatePosition(dt);
            }

            void updatePosition(float dt) {
                for(auto& obj : objects) {
                    obj->updatePos(dt);
                }
            }

            void applyGravity() {
                for(auto& planet : objects) {
                    for(auto& sputnik : objects) {
                        if(planet.get() == sputnik.get())
                            continue;

                        auto vec = planet->posCurrent - sputnik->posCurrent;
                        auto dist = vec.length();
                        auto normal = vec.normalize();

                        auto g = (normal * 9.8 * planet->mass) / (dist * dist);

                        sputnik->accelerate(g);
                    }
                }
            }

            void render(Camera& camera, GraphicsContext& context) {
                if(context.is_debug()) {
                    auto lineShader = context.get_line_shader();
                    lineShader->enable();
                    lineShader->set_uniform("translation", Mat4f::identity());
                    lineShader->set_uniform("rotation", Mat4f::identity());

                    context.render_line({0, 0, 0}, {5, 0, 0}, ColorRGBA::RED);
                    context.render_line({0, 0, 0}, {0, 5, 0}, ColorRGBA::BLUE);
                    context.render_line({0, 0, 0}, {0, 0, 5}, ColorRGBA::GREEN);
                }

                for(auto& obj : objects)
                    obj->render(context);

                Ray ray(camera.get_position(), camera.get_direction());

                for(auto& obj : objects) {
                    if(obj->get_type() != STRUCTURE)
                        continue;

                    Box box(obj->posCurrent, { obj->posCurrent.x + 16, obj->posCurrent.y + 16, obj->posCurrent.z + 16 });

                    float tmin = box.intersect(ray);
                    if(tmin > 0.0f) {
                        auto& chunk = ((Structure*) obj.get())->get_chunks()[0];

                        for(int x = 0; x < 16; ++x) {
                            for(int y = 0; y < 16; ++y) {
                                for (int z = 0; z < 16; ++z) {
                                    Box bbbb(
                                        { obj->posCurrent.x + x, obj->posCurrent.y + y, obj->posCurrent.z + z},
                                        { obj->posCurrent.x + x + 1, obj->posCurrent.y + y + 1, obj->posCurrent.z + z + 1});

                                    float t = bbbb.intersect(ray);
                                    if(t > 0.0f) {
                                        chunk->tiles[x][y][z] = 0;
                                    }
                                }
                            }
                        }

                        chunk->build_mesh();

                        // std::cout << camera.get_position() + camera.get_direction().normalize() * tmin << "\n";
                    }
                }
            }
    };
}

#endif
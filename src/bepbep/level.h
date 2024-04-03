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
                objects.push_back(std::make_shared<Structure>(Vec3f{24, 0, 0}, 5000));

                objects.push_back(std::make_shared<Structure>(Vec3f{100, 0, 0}, 1000));
                objects.push_back(std::make_shared<Structure>(Vec3f{-100, 50, 50}, 1000));

                for(int i = 0; i < 200; ++i) {
                    float x = (rand() % 200) - 100;
                    float y = (rand() % 200) - 100;
                    float z = (rand() % 200) - 100;

                    objects.push_back(std::make_shared<Entity>(Vec3f{x, y, z}, 10));
                }
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

                        auto g = (normal * 9.0 * planet->mass) / (dist * dist);

                        sputnik->accelerate(g);
                    }
                }

                // for(auto& obj : objects) {
                //     obj->accelerate({0, -9.8, 0});
                // }
            }

            void render(GraphicsContext& context) {
                context.render_line({0, 0, 0}, {5, 0, 0}, ColorRGBA::RED);
                context.render_line({0, 0, 0}, {0, 5, 0}, ColorRGBA::BLUE);
                context.render_line({0, 0, 0}, {0, 0, 5}, ColorRGBA::GREEN);

                for(auto& obj : objects)
                    obj->render(context);
            }
    };
}

#endif
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
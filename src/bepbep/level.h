#ifndef _BEPBEP_LEVEL_H_
#define _BEPBEP_LEVEL_H_

#include "entity.h"

namespace bepbep {
    class Level {
        private:
            std::vector<std::shared_ptr<Object>> objects;

        public:
            Level() {
                objects.push_back(std::make_shared<Entity>());
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
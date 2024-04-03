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

            void render(GLShaderProgram& shader) {
                for(auto& obj : objects)
                    obj->render(shader);
            }
    };
}

#endif
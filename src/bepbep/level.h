#ifndef _BEPBEP_LEVEL_H_
#define _BEPBEP_LEVEL_H_

#include "entity.h"
#include "structure.h"

namespace bepbep {
    class Level {
        private:
            vector<Object*> objects;

        public:
            Level() {
                objects.push_back(new Entity("models/suzanne.obj", Vec3f{2, 0, 0}, 1));

                objects.push_back(new Structure(Vec3f{-2, -17, 8}, 1));

                for(int i = 0; i < 5; ++i) {
                    float a = ((i / 5.0f) * 2 * 3.14159265359);
                    
                    objects.push_back(new Entity("models/bunny.obj", Vec3f{sin(a) * 7, 10, cos(a) * 7}, 1));
                }
            }

            vector<Object*>& get_objects() {
                return objects;
            }
    };
}

#endif
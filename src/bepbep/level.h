#ifndef _BEPBEP_LEVEL_H_
#define _BEPBEP_LEVEL_H_

#include "entity.h"
#include "structure.h"

namespace bepbep {
    class Level {
        private:
            vector<Object*> objects;

        public:
            Level();

            vector<Object*>& get_objects();
    };
}

#endif
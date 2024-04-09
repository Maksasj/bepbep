#ifndef _BEPBEP_PLAYER_H_
#define _BEPBEP_PLAYER_H_

#include "entity.h"

namespace bepbep {
    class Player : public Entity {
        private:

        public:
            Player(const Vec3f& pos, const float& m) : Entity(pos, m) {
                renderer = new CapsuleRenderer(0.5, 0.5, 3);
            }
    };
}

#endif
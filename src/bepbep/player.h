#ifndef _BEPBEP_PLAYER_H_
#define _BEPBEP_PLAYER_H_

#include "level/entity.h"

namespace bepbep {
    class Player : public Entity {
        private:

        public:
            Player(const Vec3f& pos, const float& m) : Entity(pos, m) {
                set_renderer(new CapsuleRenderer(0.5, 0.5, 3));
            }
    };
}

#endif
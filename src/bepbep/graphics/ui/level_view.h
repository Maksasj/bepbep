#ifndef _BEPBEP_LEVEL_VIEW_WINDOW_H_
#define _BEPBEP_LEVEL_VIEW_WINDOW_H_

#include <functional>
#include "common_window.h"

#include "level/level.h"
#include "render_pass.h"

namespace bepbep {
    class LevelViewWindow : public CommonWindow {
        private:
            ImVec2 oldSize;

        public:
            LevelViewWindow();
            ~LevelViewWindow();

            pair<bool, ImVec2> run(Level* level, RenderPass* pass);
    };
}

#endif
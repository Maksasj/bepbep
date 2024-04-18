#include "level_view.h"

namespace bepbep {
    LevelViewWindow::LevelViewWindow()
        : CommonWindow("Level View"),
          oldSize(0, 0)
    {

    }

    LevelViewWindow::~LevelViewWindow() {

    }

    pair<bool, ImVec2> LevelViewWindow::run(Level* level, RenderPass* pass) {
        static bool open = true;

        ImGui::Begin("Level View", &open, 0);

        auto levelView = pass->get_texture();

        auto size = ImGui::GetWindowSize();

        auto imageSize = ImVec2(levelView->get_width(), levelView->get_height());
        ImGui::Image((void*) levelView->get_id(), imageSize);

        ImGui::End();

        if((size.x != oldSize.x) || (size.y != oldSize.y)) {
            oldSize = size;
            return make_pair(true, oldSize);
        }

        return make_pair(false, oldSize);
    }
}

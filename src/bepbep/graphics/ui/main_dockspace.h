#ifndef _BEPBEP_MAIN_DOCKSPACE_WINDOW_H_
#define _BEPBEP_MAIN_DOCKSPACE_WINDOW_H_

#include <functional>
#include "common_window.h"

namespace bepbep {
    class MainDockspaceWindow : public CommonWindow {
        private:

        public:
            MainDockspaceWindow();
            ~MainDockspaceWindow();

            void run(const function<void(void)>& dockSpaceBody);
    };
}

#endif
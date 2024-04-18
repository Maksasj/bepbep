#ifndef _BEPBEP_COMMON_WINDOW_H_
#define _BEPBEP_COMMON_WINDOW_H_

#include "bebone/bebone.h"

#include <string>

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;
    using namespace std;

    class CommonWindow {
        private:
            const string title;
            bool focused;
            bool open;

            void update_iternal_state();

        protected:
            bool start_window();

            void end_window();

        public:
            CommonWindow(const string& title, const bool& open = true);

            virtual ~CommonWindow();

            const bool& is_focused() const;
            const bool& is_open() const;
            bool& ref_open_flag();

            void force_open();
            void force_close();
    };
}

#endif
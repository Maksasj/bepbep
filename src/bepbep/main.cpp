#include "bepbep.h"

using namespace bepbep;

int main() {
    BepBepApp app;

    app.preinit();
    app.init();
    app.load();
    app.run();
    app.cleanup();

    return 0;
}
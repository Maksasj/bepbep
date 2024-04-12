#include "graphics_context.h"

namespace bepbep {
    GraphicsContext::GraphicsContext(const bool& debug, IMaterial* material)
        : debugMode(debug),
          activeMaterial(material)
    {

    }

    const bool& GraphicsContext::is_debug() const {
        return debugMode;
    }

    IMaterial* GraphicsContext::get_active_material() {
        return activeMaterial;
    }
}

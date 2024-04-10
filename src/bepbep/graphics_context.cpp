#include "graphics_context.h"

namespace bepbep {
    GraphicsContext::GraphicsContext(const bool& debug, Material* material)
        : debugMode(debug),
          activeMaterial(material)
    {

    }

    const bool& GraphicsContext::is_debug() const {
        return debugMode;
    }

    Material* GraphicsContext::get_active_material() {
        return activeMaterial;
    }
}

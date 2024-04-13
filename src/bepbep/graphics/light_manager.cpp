#include "light_manager.h"

namespace bepbep {
    LightManager::LightManager() {
        lights.lightCount = 0;

        buffer = make_unique<GLUniformBufferObject>(sizeof(Lights));
    }

    void LightManager::add_light(const Light& light) {
        lights.lights[lights.lightCount] = light;
        ++lights.lightCount;
    }

    void LightManager::bind(GLShaderProgram* shader) {
        buffer->bind();
        shader->bind_buffer("Lights", 0, *buffer);

        auto ptr = buffer->map();
        memcpy(ptr, &lights, sizeof(Lights));

        buffer->unmap();
        buffer->unbind();
    }
}

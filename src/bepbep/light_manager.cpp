#include "light_manager.h"

namespace bepbep {

    LightManager::LightManager() {
        lightCount = 0;

        buffer = make_unique<GLUniformBufferObject>(sizeof(Lights));
    }

    void LightManager::add_light(const Light& light) {
        lights[lightCount] = light;
        ++lightCount;
    }

    void LightManager::bind(GLShaderProgram* shader) {
        buffer->bind();
        shader->bind_buffer("Lights", 0, *buffer);

        auto ptr = static_cast<Lights*>(buffer->map());

        for(int i = 0; i < lightCount; ++i) {
            ptr->lights[i] = lights[i];
        }

        ptr->lightCount = lightCount;
        buffer->unmap();

        buffer->unbind();
    }

    /*
    void LightManager::render(GraphicsContext& context) {
        auto shader = context.get_line_shader();
        shader->enable();

        for(int i = 0; i < lightCount; ++i) {
            shader->set_uniform("transform", Mat4f::translation(lights[i].origin));
            context.render_sphere();
        }
    }
    */
}

#ifndef _BEPBEP_RENDER_PASS_H_
#define _BEPBEP_RENDER_PASS_H_

#include "opengl_framebuffer.h"
#include "opengl_render_buffer.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class RenderPass {
        protected:
            unique_ptr<GLFrameBuffer> frameBuffer;
            unique_ptr<GLTexture2D> texture;
            unique_ptr<GLRenderBuffer> renderBuffer;

        public:
            RenderPass(const int& width, const int& height) {
                frameBuffer = make_unique<GLFrameBuffer>();
                frameBuffer->bind();

                texture = make_unique<GLTexture2D>(width, height);
                frameBuffer->texture2d(*texture, GL_COLOR_ATTACHMENT0);

                renderBuffer = make_unique<GLRenderBuffer>();
                renderBuffer->bind();
                renderBuffer->storage(GL_DEPTH24_STENCIL8, width, height);
                renderBuffer->framebuffer(GL_DEPTH_STENCIL_ATTACHMENT);

                frameBuffer->unbind();
            }

            void bind() {
                frameBuffer->bind();
            }

            void unbind() {
                frameBuffer->unbind();
            }

            void bind_texture() {
                texture->bind();
            }

            void unbind_texture() {
                texture->unbind();
            }
    };
}

#endif
#ifndef _BEPBEP_OPENGL_FRAMEBUFFER_H_
#define _BEPBEP_OPENGL_FRAMEBUFFER_H_

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
// #define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class GLFrameBuffer {
        protected:
            GLuint id;

        public:
            GLFrameBuffer() {
                glGenFramebuffers(1, &id);
            }

            ~GLFrameBuffer() {
                glDeleteFramebuffers(1, &id);
            }

            void bind() {
                glBindFramebuffer(GL_FRAMEBUFFER, id);
            }

            void unbind() {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            void texture2d(GLTexture2D& texture, GLuint attachment) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, texture.get_texture_type(), texture.get_id(), 0);
            }
    };
}

#endif
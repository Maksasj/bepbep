#ifndef _BEPBEP_OPENGL_RENDER_BUFFER_H_
#define _BEPBEP_OPENGL_RENDER_BUFFER_H_

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
// #define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class GLRenderBuffer {
        protected:
            GLuint id;

        public:
            GLRenderBuffer() {
                glGenRenderbuffers(1, &id);
            }

            void bind() const {
                glBindRenderbuffer(GL_RENDERBUFFER, id);
            }

            void unbind() const {
                glBindRenderbuffer(GL_RENDERBUFFER, 0);
            }

            void storage(GLenum format, GLsizei width, GLsizei height) const {
                glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
            }

            void framebuffer(GLenum attachment) const {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, id);
            }
    };
}

#endif
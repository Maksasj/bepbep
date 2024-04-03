#ifndef _BEPBEP_GRAPHICS_CONTEXT_H_
#define _BEPBEP_GRAPHICS_CONTEXT_H_

#include "mesh.h"

namespace bepbep {
    class GraphicsContext {
        private:
            bool debugMode;

            GLShaderProgram* mainShader;
            GLShaderProgram* lineShader;

        public:
            GraphicsContext();

            void set_debug_mode(const bool& value);
            void set_main_shader(GLShaderProgram* shader);
            void set_line_shader(GLShaderProgram* shader);

            const bool& is_debug() const;
            GLShaderProgram* get_main_shader();
            GLShaderProgram* get_line_shader();
    };
}

#endif
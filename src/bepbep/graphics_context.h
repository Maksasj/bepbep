#ifndef _BEPBEP_GRAPHICS_CONTEXT_H_
#define _BEPBEP_GRAPHICS_CONTEXT_H_

#include "mesh.h"
#include "line_mesh.h"


namespace bepbep {
    class GraphicsContext {
        private:
            bool debugMode;

            GLShaderProgram* mainShader;
            GLShaderProgram* lineShader;

            unique_ptr<LineMesh> line;

    public:
            GraphicsContext();

            void set_debug_mode(const bool& value);
            void set_main_shader(GLShaderProgram* shader);
            void set_line_shader(GLShaderProgram* shader);

            void init_line_mesh() {
                LineVertex vertices[] = {
                    {{0, 0, 0}, ColorRGBA::WHITE },
                    {{0, 0, 0}, ColorRGBA::WHITE },
                };

                line = make_unique<LineMesh>(vertices, 2);
            }

            void render_line(const Vec3f& start, const Vec3f& end, const ColorRGBA& color) {
                if(lineShader != nullptr) {
                    LineVertex vertices[2] = {
                        { start, color },
                        { end, color },
                    };

                    line->update_vertices(vertices, 2);

                    lineShader->enable();

                    line->render();
                }
            }

            void render_line(const Vec3f& start, const Vec3f& end, const Vec3f& translation, const ColorRGBA& color) {
                if(lineShader != nullptr) {
                    LineVertex vertices[2] = {
                            { start + translation, color },
                            { end + translation, color },
                    };

                    line->update_vertices(vertices, 2);

                    lineShader->enable();

                    line->render();
                }
            }

            const bool& is_debug() const;
            GLShaderProgram* get_main_shader();
            GLShaderProgram* get_line_shader();
    };
}

#endif
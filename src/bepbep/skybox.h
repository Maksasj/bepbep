#ifndef _BEPBEP_SKYBOX_H_
#define _BEPBEP_SKYBOX_H_

#include "pbr_material.h"
#include "mesh.h"
#include "model.h"
#include "mesh_builder.h"
#include "transform.h"
#include "irenderable.h"

namespace bepbep {
    using namespace bebone::core;

    class SkyBoxRenderer : public Renderer {
        private:
            unique_ptr<GLVertexArrayObject> vao;
            unique_ptr<GLVertexBufferObject> vbo;

        public:
            SkyBoxRenderer() {
                static vector<Vec3f> skyboxVertices = {
                    // positions
                    {-1.0f,  1.0f, -1.0f},
                    {-1.0f, -1.0f, -1.0f},
                    {1.0f, -1.0f, -1.0f},
                    {1.0f, -1.0f, -1.0f},
                    {1.0f,  1.0f, -1.0f},
                    {-1.0f,  1.0f, -1.0f},

                    {-1.0f, -1.0f,  1.0f},
                    {-1.0f, -1.0f, -1.0f},
                    {-1.0f,  1.0f, -1.0f},
                    {-1.0f,  1.0f, -1.0f},
                    {-1.0f,  1.0f,  1.0f},
                    {-1.0f, -1.0f,  1.0f},

                    {1.0f, -1.0f, -1.0f},
                    {1.0f, -1.0f,  1.0f},
                    {1.0f,  1.0f,  1.0f},
                    {1.0f,  1.0f,  1.0f},
                    {1.0f,  1.0f, -1.0f},
                    {1.0f, -1.0f, -1.0f},

                    {-1.0f, -1.0f,  1.0f},
                    {-1.0f,  1.0f,  1.0f},
                    {1.0f,  1.0f,  1.0f},
                    {1.0f,  1.0f,  1.0f},
                    {1.0f, -1.0f,  1.0f},
                    {-1.0f, -1.0f,  1.0f},

                    {-1.0f,  1.0f, -1.0f},
                    {1.0f,  1.0f, -1.0f},
                    {1.0f,  1.0f,  1.0f},
                    {1.0f,  1.0f,  1.0f},
                    {-1.0f,  1.0f,  1.0f},
                    {-1.0f,  1.0f, -1.0f},

                    {-1.0f, -1.0f, -1.0f},
                    {-1.0f, -1.0f,  1.0f},
                    {1.0f, -1.0f, -1.0f},
                    {1.0f, -1.0f, -1.0f},
                    {-1.0f, -1.0f,  1.0f},
                    {1.0f, -1.0f,  1.0f}
                };

                vao = make_unique<GLVertexArrayObject>();
                vao->bind();

                vbo = make_unique<GLVertexBufferObject>(skyboxVertices.data(), skyboxVertices.size() * sizeof(Vec3f));

                vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(Vec3f), nullptr);

                vao->unbind();
                vbo->unbind();
            }

            void render(GraphicsContext& context, const Transform& transform) override {
                vao->bind();

                GLContext::draw_arrays(GL_TRIANGLES, 0, 36);
            }
    };

    class SkyBox : public IRenderable {
        private:

        public:
            SkyBox(IMaterial* material) : IRenderable() {
                set_material(material);
                set_renderer(new SkyBoxRenderer());
            }
    };
}

#endif
#ifndef _BEPBEP_TEXTURE_MANAGER_H_
#define _BEPBEP_TEXTURE_MANAGER_H_

#include "material.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class TextureManager {
        private:
            unordered_map<string, GLTexture2D*> textures;

        public:
            GLTexture2D* load_texture(const string& name, const string& path) {
                auto* texture = new GLTexture2D(path);

                textures[name] = texture;

                return texture;
            }

            GLTexture2D* load_color_texture(const string& name, const ColorRGBA& color) {
                auto image = Image<ColorRGBA>::from_color(64, 64, color);
                auto* texture = new GLTexture2D(image);

                textures[name] = texture;

                return texture;
            }

            GLTexture2D* get_texture(const string& name) {
                return textures[name];
            }

    };
}

#endif
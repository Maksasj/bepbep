#ifndef _BEPBEP_TEXTURE_MANAGER_H_
#define _BEPBEP_TEXTURE_MANAGER_H_

#include "pbr_material.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class TextureManager {
        private:
            unordered_map<string, GLTexture*> textures;

        public:
            GLTexture* load_texture(const string& name, const string& path) {
                auto* texture = new GLTexture2D(path);
                textures[name] = texture;
                return texture;
            }

            GLTexture* load_texture(const string& name, const std::vector<std::string>& filePaths) {
                auto* texture = new GLTextureCubeMap(filePaths);
                textures[name] = texture;
                return texture;
            }

            GLTexture* load_color_texture(const string& name, const ColorRGBA& color) {
                auto* texture = new GLTexture2D(Image<ColorRGBA>::from_color(64, 64, color));
                textures[name] = texture;
                return texture;
            }

            GLTexture* get_texture(const string& name) {
                return textures[name];
            }

    };
}

#endif
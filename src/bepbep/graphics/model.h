#ifndef _BEPBEP_MODEL_H_
#define _BEPBEP_MODEL_H_

#include "graphics/mesh.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Model {
        private:
            unique_ptr<Mesh> mesh;

            static vector<string> split(const string& s, const string& delimiter);

        public:
            Model(unique_ptr<Mesh> m);

            void render();

            static shared_ptr<Model> load_from_obj(const string& filePath);
    };

}

#endif
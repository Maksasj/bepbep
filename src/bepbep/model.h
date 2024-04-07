#ifndef _BEPBEP_MODEL_H_
#define _BEPBEP_MODEL_H_

#include "mesh.h"

namespace bepbep {
    using namespace bebone::core;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    class Model {
        private:
            unique_ptr<Mesh> mesh;

        public:
            Model(unique_ptr<Mesh> m) {
                mesh = move(m);
            }

            void render() {
                mesh->render();
            }

            static shared_ptr<Model> load_from_obj(const string& filePath) {
                ifstream file(filePath);

                vector<Vertex> rawVertices;
                vector<Vertex> vertices;
                vector<u32> indicies;

                u32 index = 0;
                unordered_map<string, u32> correctedIndex;

                string line;
                while(getline(file, line)) {
                    stringstream data(line);

                    std::string keyword;
                    data >> keyword;

                    if(keyword == "v") {
                        f32 x, y, z;
                        data >> x >> y >> z;

                        auto val = (rand() % 255) / 255.0f;
                        rawVertices.push_back({ Vec3f{x, y, z}, ColorRGBA::splat(val)});
                    } else if(keyword == "f") {
                        string in[3];
                        data >> in[0] >> in[1] >> in[2];

                        for(auto& i : in) {
                            auto v = i.substr(0, i.find("/"));

                            if(!correctedIndex.contains(v)) {
                                correctedIndex.insert(make_pair(v, index));
                                vertices.push_back(rawVertices[std::stoi(v) - 1]);
                                ++index;
                            }

                            indicies.push_back(correctedIndex[v]);
                        }
                    }
                }

                return make_shared<Model>(make_unique<Mesh>(vertices, indicies));
            }
    };

}

#endif
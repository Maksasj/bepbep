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

            static vector<string> split(string s, string delimiter) {
                size_t pos_start = 0, pos_end, delim_len = delimiter.length();
                string token;
                vector<string> res;

                while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
                    token = s.substr (pos_start, pos_end - pos_start);
                    pos_start = pos_end + delim_len;
                    res.push_back (token);
                }

                res.push_back (s.substr (pos_start));
                return res;
            }

        public:
            Model(unique_ptr<Mesh> m) {
                mesh = move(m);
            }

            void render() {
                mesh->render();
            }

            static shared_ptr<Model> load_from_obj(const string& filePath) {
                ifstream file(filePath);

                vector<Vec3f> rawVertices;
                vector<Vec3f> rawNormals;

                vector<Vertex> vertices;
                vector<u32> indicies;

                u32 index = 0;
                unordered_map<string, u32> correctedIndex;

                string line;
                while(getline(file, line)) {
                    stringstream data(line);

                    string keyword;
                    data >> keyword;

                    if(keyword == "v") {
                        f32 x, y, z;
                        data >> x >> y >> z;
                        rawVertices.emplace_back(x, y, z);
                    } else if(keyword == "vn") {
                        f32 x, y, z;
                        data >> x >> y >> z;
                        rawNormals.emplace_back(x, y, z);
                    } else if(keyword == "f") {
                        string in[3];
                        data >> in[0] >> in[1] >> in[2];

                        for(auto& i : in) {
                            auto v = split(i, "/");

                            if(!correctedIndex.contains(v[0])) {
                                correctedIndex.insert(make_pair(v[0], index));

                                auto vertex = rawVertices[stoi(v[0]) - 1];

                                auto normal = Vec3f::zero;
                                if(v.size() >= 3)
                                    normal = rawNormals[stoi(v[2]) - 1];

                                vertices.push_back({
                                    vertex,
                                    normal,
                                    ColorRGBA::WHITE
                                });

                                ++index;
                            }

                            indicies.push_back(correctedIndex[v[0]]);
                        }
                    }
                }

                return make_shared<Model>(make_unique<Mesh>(vertices, indicies));
            }
    };

}

#endif
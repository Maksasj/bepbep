#include "model.h"

namespace bepbep {
    vector<string> Model::split(const string& s, const string& delimiter) {
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

    Model::Model(unique_ptr<Mesh> m) {
        mesh = move(m);
    }

    void Model::render() {
        mesh->render();
    }

    shared_ptr<Model> Model::load_from_obj(const string& filePath) {
        ifstream file(filePath);

        vector<Vec3f> rawVertices;
        vector<Vec3f> rawNormals;
        vector<Vec2f> rawTexCord;

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
            } else if(keyword == "vt") {
                f32 x, y;
                data >> x >> y;
                rawTexCord.emplace_back(x, y);
            } else if(keyword == "vn") {
                f32 x, y, z;
                data >> x >> y >> z;
                rawNormals.emplace_back(x, y, z);
            } else if(keyword == "f") {
                string in[3];
                data >> in[0] >> in[1] >> in[2];

                for(int o = 0; o < 3; ++o) {
                    auto i = in[o];
                    auto v = split(i, "/");

                    if(!correctedIndex.contains(v[0])) {
                        correctedIndex.insert(make_pair(v[0], index));

                        auto vertex = rawVertices[stoi(v[0]) - 1];

                        auto normal = Vec3f::zero;
                        if(v.size() >= 3 && !v[2].empty())
                            normal = rawNormals[stoi(v[2]) - 1];

                        const static Vec2f repTexCord[] = {
                            {0.0f, 0.0f},
                            {0.0f, 1.0f},
                            {1.0f, 0.0f}
                        };

                        auto texCord = repTexCord[o];

                        if(v.size() >= 3 && rawTexCord.size() >= 0 && !v[1].empty())
                            texCord = rawTexCord[stoi(v[1]) - 1];

                        vertices.emplace_back(vertex, normal, texCord);
                        ++index;
                    }

                    indicies.push_back(correctedIndex[v[0]]);
                }
            }
        }

        return make_shared<Model>(make_unique<Mesh>(vertices, indicies));
    }
}

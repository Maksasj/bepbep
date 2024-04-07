#include "block.h"
#include "chunk.h"

namespace bepbep {
    Block::Block(const Vec3i& pos) : chunkPos(pos) {

    }

    StoneBlock::StoneBlock(const Vec3i& pos) : Block(pos) {}

    void StoneBlock::append_mesh(Chunk* chunk, MeshBuilder& builder) {
        static const vector<u32> indices = {
                0, 2, 3,
                0, 3, 1,

                4, 6, 7,
                4, 7, 5,

                8, 10, 11,
                8, 11, 9,

                12, 14, 15,
                12, 15, 13,

                16, 18, 19,
                16, 19, 17,

                20, 22, 23,
                20, 23, 21
        };

        auto color = ColorRGBA::splat(0.7);

        static const vector<Vertex> vertices = {
            {{0.0f, 0.0f, 0.0f}, { 0 , 0, -1}, color},
            {{1.0f, 0.0f, 0.0f}, { 0 , 0, -1}, color},
            {{0.0f, 1.0f, 0.0f}, { 0 , 0, -1}, color},
            {{1.0f, 1.0f, 0.0f}, { 0 , 0, -1}, color},

            {{1.0f, 0.0f, 1.0f}, { 0, 0, 1 },  color},
            {{0.0f, 0.0f, 1.0f}, { 0, 0, 1 },  color},
            {{1.0f, 1.0f, 1.0f}, { 0, 0, 1 },  color},
            {{0.0f, 1.0f, 1.0f}, { 0, 0, 1 },  color},

            {{0.0f, 0.0f, 1.0f}, { -1 , 0, 0}, color},
            {{0.0f, 0.0f, 0.0f}, { -1 , 0, 0}, color},
            {{0.0f, 1.0f, 1.0f}, { -1 , 0, 0}, color},
            {{0.0f, 1.0f, 0.0f}, { -1 , 0, 0}, color},

            {{1.0f, 0.0f, 0.0f}, { 1, 0, 0 },  color},
            {{1.0f, 0.0f, 1.0f}, { 1, 0, 0 },  color},
            {{1.0f, 1.0f, 0.0f}, { 1, 0, 0 },  color},
            {{1.0f, 1.0f, 1.0f}, { 1, 0, 0 },  color},

            // Up
            {{0.0f, 1.0f, 0.0f}, { 0 , 1, 0 }, color},
            {{1.0f, 1.0f, 0.0f}, { 0 , 1, 0 }, color},
            {{0.0f, 1.0f, 1.0f}, { 0 , 1, 0 }, color},
            {{1.0f, 1.0f, 1.0f}, { 0 , 1, 0 }, color},

            // Bottom
            {{0.0f, 0.0f, 1.0f}, { 0 , -1, 0 },color},
            {{1.0f, 0.0f, 1.0f}, { 0 , -1, 0 },color},
            {{0.0f, 0.0f, 0.0f}, { 0 , -1, 0 },color},
            {{1.0f, 0.0f, 0.0f}, { 0 , -1, 0 },color}
        };

        const Vec3f translation = {
            static_cast<f32>(chunkPos.x),
            static_cast<f32>(chunkPos.y),
            static_cast<f32>(chunkPos.z)
        };

        builder.append(vertices, indices, translation);
    }
}

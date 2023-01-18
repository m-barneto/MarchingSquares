#pragma once
#include <map>
#include "Point.h"
#include "Chunk.h"

#include "../FastNoiseLite.h"

class ChunkManager {
private:
    std::map<Point, Chunk> chunks;
    FastNoiseLite noise;
public:
    ChunkManager() {
        noise = FastNoiseLite();
    }

    Chunk& getChunk(Point coord) {
        if (chunks.find(coord) == chunks.end()) {
            // gen new chunk
            Chunk chunk{};
            chunk.data = new bool[chunk.SIZE * chunk.SIZE];
            for (int y = 0; y < chunk.SIZE; y++) {
                for (int x = 0; x < chunk.SIZE; x++) {
                    chunk.data[x + (y * chunk.SIZE)] = noise.GetNoise((float)x, (float)y);
                }
            }
            chunks[coord] = chunk;

            return chunks[coord];
        } else {
            // chunk already exists
            return chunks.at(coord);
        }
    }
};
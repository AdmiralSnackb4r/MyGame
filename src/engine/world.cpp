#include "world.hpp"

World::World::World() {
    #ifdef DEBUG_MODE
        std::cout << "World Object created" << std::endl;
    #endif
    generateWorld();
}

World::World::~World() {
    #ifdef DEBUG_MODE
        std::cout << "World Object deleted" << std::endl;
    #endif

}

void World::World::generateWorld() {
    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            if (y < (WORLD_HEIGHT * PERCENTAGE_SKY)) {    // SKY GENERATION
                mMap[y][x] = 0;
            }

            else if (y > (WORLD_HEIGHT * PERCENTAGE_SKY)) { // GROUND GENERATION
                mMap[y][x] = 1;
            }
        }
    }
}

void World::World::renderWorld(SDL_Renderer *&renderer) {
    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            const SDL_FRect tileRect = {x * static_cast<float>(TILE_SIZE),
                                        y * static_cast<float>(TILE_SIZE),
                                        static_cast<float>(TILE_SIZE),
                                        static_cast<float>(TILE_SIZE)};
            SDL_SetRenderDrawColor(renderer, mMap[y][x] ? 139 : 200, mMap[y][x] ? 69 : 200, mMap[y][x] ? 19 : 200, 255);
            SDL_RenderFillRect(renderer, &tileRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderRect(renderer, &tileRect);
        }
    }
}

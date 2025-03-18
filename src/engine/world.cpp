#include "world.hpp"

World::World::World(Player::Player* player) {
    #ifdef DEBUG_MODE
        std::cout << "World Object created" << std::endl;
    #endif

    updateCamera(player);
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
            
            // Tile position relative to camera
            int tileX = x * TILE_SIZE - mCamera.x;
            int tileY = y * TILE_SIZE - mCamera.y;

            // Render only if within screent
            if (tileX + TILE_SIZE > 0 && tileX < SCREEN_WIDTH &&
                tileY + TILE_SIZE > 0 && tileY < SCREEN_HEIGHT) {


                const SDL_FRect tileRect = {tileX, tileY, TILE_SIZE, TILE_SIZE};

                SDL_SetRenderDrawColor(renderer, mMap[y][x] ? 139 : 200, mMap[y][x] ? 69 : 200, mMap[y][x] ? 19 : 200, 255);
                SDL_RenderFillRect(renderer, &tileRect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderRect(renderer, &tileRect);
            }
        }
    }
}

void World::World::updateCamera(Player::Player *player) {

    mCamera.x = player->getPosition().x - SCREEN_WIDTH/2;
    mCamera.y = player->getPosition().y - SCREEN_HEIGHT/2;

    if (mCamera.x < 0) mCamera.x = 0;
    if (mCamera.y < 0) mCamera.y = 0;
    if (mCamera.x > WORLD_WIDTH * TILE_SIZE - SCREEN_WIDTH)
        mCamera.x = WORLD_WIDTH * TILE_SIZE - SCREEN_WIDTH;
    if (mCamera.y > WORLD_HEIGHT * TILE_SIZE - SCREEN_HEIGHT)
        mCamera.y = WORLD_HEIGHT * TILE_SIZE - SCREEN_HEIGHT;

}

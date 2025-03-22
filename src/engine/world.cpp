#include "world.hpp"

namespace World {
    fs::path basePath = PROJECT_ROOT;
    fs::path textures = "textures";
    fs::path world = "world";

    fs::path background = "Background.bmp";
    fs::path dirt = "Dirt.bmp";

    fs::path backgroundBMP = basePath / textures / world / background;
    fs::path dirtBMP = basePath / textures / world / dirt;
}


SDL_Texture *World::World::loadTexture(const std::string &path, SDL_Renderer *renderer) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
                if (!surface) {
                    SDL_Log("Failed to load texture: %s", SDL_GetError());
                    return nullptr;
                }
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (!texture) {
                    SDL_Log("Failed to create texture: %s", SDL_GetError());
                }
                SDL_DestroySurface(surface);
                return texture;
}

World::World::World(Player::Player *player, SDL_Renderer* renderer) {
#if DEBUG_MODE
    std::cout << "World Object created" << std::endl;
#endif

    mCamera.x = player->getPosition().x - SCREEN_WIDTH/2;
    mCamera.y = player->getPosition().y - SCREEN_HEIGHT/2;

    mTileTextures[0] = loadTexture(backgroundBMP.string(), renderer);
    mTileTextures[1] = loadTexture(dirtBMP.string(), renderer);

    updateCamera(player);
    generateWorld();
}

World::World::~World() {
    #if DEBUG_MODE
        std::cout << "World Object deleted" << std::endl;
    #endif
    SDL_DestroyTexture(mTileTextures[0]);
    SDL_DestroyTexture(mTileTextures[1]);

}

const SDL_FRect World::World::getMovementArea()
{
    return mPlayerMoveArea;
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

    int startX = std::max(0, mCamera.x / TILE_SIZE);
    int startY = std::max(0, mCamera.y / TILE_SIZE);
    int endX = std::min(WORLD_WIDTH, (mCamera.x + SCREEN_WIDTH) / TILE_SIZE + 1);
    int endY = std::min(WORLD_HEIGHT, (mCamera.y + SCREEN_HEIGHT) / TILE_SIZE + 1);

    SDL_FRect tileRect;
    tileRect.w = TILE_SIZE;
    tileRect.h = TILE_SIZE;

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {

            tileRect.x = x * TILE_SIZE - mCamera.x;
            tileRect.y = y * TILE_SIZE - mCamera.y;

            SDL_RenderTexture(renderer, mTileTextures[mMap[y][x]], nullptr, &tileRect);

        }
    }
    #if DEBUG_MODE
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderRect(renderer, &mPlayerMoveArea);
    #endif
}

void World::World::updateCamera(Player::Player *player) {

    if (player->getPosition().x - player->getPosition().w <= mPlayerMoveArea.x) {
        // Player hits the left boundary -> Move the world to the right
        mCamera.x = std::max(0, static_cast<int>(mCamera.x - player->getMovingDirection().velocityX));
    } 
    else if (player->getPosition().x + player->getPosition().w >= mPlayerMoveArea.x + mPlayerMoveArea.w) {
        // Player hits the right boundary -> Move the world to the left
        mCamera.x = std::min(WORLD_WIDTH * TILE_SIZE - SCREEN_WIDTH, static_cast<int>(mCamera.x + player->getMovingDirection().velocityX));
    }

}

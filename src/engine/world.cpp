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

    mCamera.x = player->getPosition().x_onScreen - SCREEN_WIDTH/2;
    mCamera.y = player->getPosition().y_onScreen - SCREEN_HEIGHT/2;

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

void World::World::addEntity(Player::Player *entity) {
    mEntities.push_back(entity);
}

const SDL_FRect* World::World::getMovementArea()
{
    return &mPlayerMoveArea;
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

    if (player->getPosition().x_onScreen - player->getPosition().w <= mPlayerMoveArea.x) {
        // Player hits the left boundary -> Move the world to the right
        mCamera.x = std::max(0, static_cast<int>(mCamera.x - player->getMovingDirection().velocityX));
    } 
    else if (player->getPosition().x_onScreen + player->getPosition().w >= mPlayerMoveArea.x + mPlayerMoveArea.w) {
        // Player hits the right boundary -> Move the world to the left
        mCamera.x = std::min(WORLD_WIDTH * TILE_SIZE - SCREEN_WIDTH, static_cast<int>(mCamera.x + player->getMovingDirection().velocityX));
    }

    if (player->getPosition().y_onScreen - player->getPosition().h <= mPlayerMoveArea.y) {
        // Player hits the upper boundary -> Move the world to the bottom
        mCamera.y = std::max(0, static_cast<int>(mCamera.y - player->getMovingDirection().velocityY));
    } 
    else if (player->getPosition().y_onScreen + player->getPosition().h >= mPlayerMoveArea.y + mPlayerMoveArea.h) {
        // Player hits the lower boundary -> Move the world to the top
        mCamera.y = std::min(WORLD_HEIGHT * TILE_SIZE - SCREEN_WIDTH, static_cast<int>(mCamera.y + player->getMovingDirection().velocityY));
    }
    

}

void World::World::update() {

    int left;
    int right;
    int bottom;

    bool onGround;

    for (Player::Player* entity : mEntities) {
        if (entity->isOnGround()) continue;

        left = entity->getPosition().x_inWorld / TILE_SIZE;
        right = (entity->getPosition().x_inWorld + entity->getPosition().w) / TILE_SIZE;
        bottom = (entity->getPosition().y_inWorld + entity->getPosition().h) / TILE_SIZE;

        onGround = false;
        for (int x = left; x <= right; ++x) {
            if (mMap[bottom][x] == 1) {
                #ifdef DEBUG_MODE
                    std::cout << "Collision with ground detected" << std::endl;
                #endif
                onGround = true;
                break;
            }
        }
        entity->setGround(onGround);
    }
}

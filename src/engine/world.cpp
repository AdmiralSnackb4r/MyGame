#include "world.hpp"

namespace World {
    fs::path basePath = PROJECT_ROOT;
    fs::path textures = "textures";
    fs::path world = "world";

    fs::path background = "Background.bmp";
    fs::path dirt = "Dirt.bmp";

    fs::path backgroundBMP = basePath / textures / world / background;
    fs::path dirtBMP = basePath / textures / world / dirt;

World::World(Player::Player *player, SDL_Renderer* renderer) : mRenderRef{renderer} {
#if DEBUG_MODE
    std::cout << "World Object created" << std::endl;
#endif

    mTileTextures[0] = textureUtils::loadTexture(backgroundBMP.string(), renderer);
    mTileTextures[1] = textureUtils::loadTexture(dirtBMP.string(), renderer);

    generateWorld();
}

World::~World() {
    #if DEBUG_MODE
        std::cout << "World Object deleted" << std::endl;
    #endif
    SDL_DestroyTexture(mTileTextures[0]);
    SDL_DestroyTexture(mTileTextures[1]);

}

void World::addEntity(Player::Player *entity) {
    entity->setMapRef(&mMap);
    mEntities.push_back(entity);

}

const SDL_FRect* World::getMovementArea()
{
    return &mPlayerMoveArea;
}

void World::generateWorld() {

    mMap = std::vector<std::vector<int>>(WORLD_HEIGHT, std::vector<int>(WORLD_WIDTH, 0));

    // Create a simple heightmap
    std::vector<int> heightMap(WORLD_WIDTH);
    int baseHeight = WORLD_HEIGHT * PERCENTAGE_SKY;

    for (int x = 0; x < WORLD_WIDTH; ++x) {
        heightMap[x] = baseHeight + (std::rand() % 5 - 2); // Small variation for hills
    }

    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            if (y < heightMap[x]) {    
                mMap[y][x] = 0; // Sky
            } else {    
                mMap[y][x] = 1; // Ground
            }
        }
    }
}

void World::renderWorld(Camera::Camera* camera) {

    int startX = std::max(0, camera->getViewport().x / TILE_SIZE);
    int startY = std::max(0, camera->getViewport().y / TILE_SIZE);
    int endX = std::min(WORLD_WIDTH, (camera->getViewport().x + SCREEN_WIDTH) / TILE_SIZE + 1);
    int endY = std::min(WORLD_HEIGHT, (camera->getViewport().y + SCREEN_HEIGHT) / TILE_SIZE + 1);

    SDL_FRect tileRect;
    tileRect.w = TILE_SIZE;
    tileRect.h = TILE_SIZE;

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {

            tileRect.x = x * TILE_SIZE - camera->getViewport().x;
            tileRect.y = y * TILE_SIZE - camera->getViewport().y;

            SDL_RenderTexture(mRenderRef, mTileTextures[mMap[y][x]], nullptr, &tileRect);

        }
    }
    #if DEBUG_MODE
    SDL_SetRenderDrawColor(mRenderRef, 0, 0, 255, 100);
    SDL_RenderRect(mRenderRef, &mPlayerMoveArea);
    #endif
}

void World::update() {

    int left;
    int right;
    int bottom;

    bool onGround;

    for (Player::Player* entity : mEntities) {
        //if (entity->isOnGround()) continue;

        left = entity->getHitbox().x / TILE_SIZE;
        right = (entity->getHitbox().x + entity->getHitbox().w) / TILE_SIZE;
        bottom = (entity->getHitbox().y + entity->getHitbox().h) / TILE_SIZE;

        onGround = false;
        for (int x = left; x <= right; ++x) {
            if (mMap[bottom][x] == 1) {
                #ifdef DEBUG_MODE
                    std::cout << "Collision with ground detected" << std::endl;
                #endif
                onGround = true;
                break;
            }
            onGround = false;
        }
        entity->setGround(onGround);
    }
}

}

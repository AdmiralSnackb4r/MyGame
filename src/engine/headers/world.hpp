#ifndef WORLD_H
#define WORLD_H

#include "config.h"
#include "textureUtils.hpp"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <filesystem>
#include "player.hpp"
#include "camera.hpp"

namespace World {

    namespace fs = std::filesystem;

    // Paths for textures and assets
    extern fs::path basePath;
    extern fs::path textures;
    extern fs::path world;
    extern fs::path background;
    extern fs::path dirt;

    extern fs::path backgroundBMP;
    extern fs::path dirtBMP;

    class World {

        private:
            std::shared_ptr<std::vector<std::vector<int>>> mMap;
            std::vector<Player::Player*> mEntities; // Temporary of type Player TODO make new class of type Entity
            SDL_Renderer* mRenderRef = nullptr;

            const SDL_FRect mPlayerMoveArea = {SCREEN_WIDTH*0.2, SCREEN_HEIGHT*0.3, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.4};
            SDL_Texture* mTileTextures[2];
            int mMovementBufferX{0};
            int mMovementBufferY{0};

        public:
            World(Player::Player* player, SDL_Renderer* renderer);
            ~World();

            void addEntity(Player::Player* entity); // TODO make this work with class Entity

            const SDL_FRect* getMovementArea();

            void generateWorld();
            void renderWorld(Camera::Camera* camera);
            //void updateCamera(Player::Player* player);
            void update();


    };


} // namespace World


#endif // WORLD_H
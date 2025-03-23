#ifndef WORLD_H
#define WORLD_H


#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "player.hpp"
#include <filesystem>
#include "config.h"

namespace World {


    namespace fs = std::filesystem;

    extern fs::path basePath;
    extern fs::path textures;
    extern fs::path world;
    extern fs::path background;
    extern fs::path dirt;

    extern fs::path backgroundBMP;
    extern fs::path dirtBMP;

    struct Camera {
        int x;
        int y;
    };

    class World {

        private:
            std::vector<std::vector<int>> mMap = std::vector<std::vector<int>>(WORLD_HEIGHT, std::vector<int>(WORLD_WIDTH, 0));
            std::vector<Player::Player*> mEntities; // Temporary of type Player TODO make new class of type Entity

            Camera mCamera;
            const SDL_FRect mPlayerMoveArea = {SCREEN_WIDTH*0.2, SCREEN_HEIGHT*0.3, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.4};
            SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* renderer);
            SDL_Texture* mTileTextures[2];
            int mMovementBufferX{0};
            int mMovementBufferY{0};

        public:
            World(Player::Player* player, SDL_Renderer* renderer);
            ~World();

            void addEntity(Player::Player* entity); // TODO make this work with class Entity

            const SDL_FRect* getMovementArea();

            void generateWorld();
            void renderWorld(SDL_Renderer*& renderer);
            void updateCamera(Player::Player* player);
            void update();


    };


} // namespace World


#endif // WORLD_H
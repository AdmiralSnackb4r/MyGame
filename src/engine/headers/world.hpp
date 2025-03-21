#ifndef WORLD_H
#define WORLD_H


#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "player.hpp"
#include <filesystem>
#include "config.h"

const int TILE_SIZE = 32;
const int WORLD_WIDTH = 250;
const int WORLD_HEIGHT = 150;
const float PERCENTAGE_SKY = 0.3f;
const float PERCENTAGE_GROUND = 1.0f - PERCENTAGE_SKY;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

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
            Camera mCamera;
            const SDL_FRect mPlayerMoveArea = {SCREEN_WIDTH*0.2, SCREEN_HEIGHT*0.3, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.4};
            SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* renderer);
            SDL_Texture* mTileTextures[2];

        public:
            World(Player::Player* player, SDL_Renderer* renderer);
            ~World();

            const SDL_FRect getMovementArea();

            void generateWorld();
            void renderWorld(SDL_Renderer*& renderer);
            void updateCamera(Player::Player* player);


    };


} // namespace World


#endif // WORLD_H
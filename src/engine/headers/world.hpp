#ifndef WORLD_H
#define WORLD_H


#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "player.hpp"

const int TILE_SIZE = 32;
const int WORLD_WIDTH = 250;
const int WORLD_HEIGHT = 150;
const float PERCENTAGE_SKY = 0.3f;
const float PERCENTAGE_GROUND = 1.0f - PERCENTAGE_SKY;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

namespace World {

    struct Camera {
        int x;
        int y;
    };

    class World {

        private:
            std::vector<std::vector<int>> mMap = std::vector<std::vector<int>>(WORLD_HEIGHT, std::vector<int>(WORLD_WIDTH, 0));
            Camera mCamera;

        public:
            World(Player::Player* player);
            ~World();

            void generateWorld();
            void renderWorld(SDL_Renderer*& renderer);
            void updateCamera(Player::Player* player);


    };


} // namespace World


#endif // WORLD_H
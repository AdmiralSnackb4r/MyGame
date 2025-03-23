#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <player.hpp>
#include <world.hpp>


#define _USE_MATH_DEFINES
#include <cmath>

constexpr double LEFT_ANGLE = M_PI;
constexpr double RIGHT_ANGLE = 0.0;

int initialize(SDL_Window*& window, SDL_Renderer*& renderer) {

    // Events Init
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        std::cerr << "SDL INIT EVENT ERROR: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Video Init
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL INIT VIDEO ERROR: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Window creation
    window = SDL_CreateWindow(
        "Game Title",
        1920, // width in pixels
        1080, // height in pixels
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    return 0;
}

int pressedKeyHandler(SDL_Event* event, Player::Player* player) {
    #if DEBUG_MODE
        std::cerr << "Key pressed: " << SDL_GetKeyName(event->key.key) << std::endl;
    #endif
    switch (event->key.key) {
        case SDLK_SPACE:
            player->jump();
            return 0;
    }
    return 0;
}

int releasedKeyHandler(SDL_Event* event, Player::Player* player) {
    #if DEBUG_MODE
        std::cerr << "Key released: " << SDL_GetKeyName(event->key.key) << std::endl;
    #endif
    switch (event->key.key) {
        case SDLK_A:
            player->setVelocity(0.0f);
            return 0;
        case SDLK_D:
            player->setVelocity(0.0f);
            return 0;
    }
    return 0;
}

int keyBoardPolling(Player::Player* player, const SDL_FRect* movementArea) {

    const bool* keyState = SDL_GetKeyboardState(nullptr);

    if (keyState[SDL_SCANCODE_D]) {
        player->walkTo(RIGHT_ANGLE, movementArea);
        return 0;
    }
    if (keyState[SDL_SCANCODE_A]) {
        player->walkTo(LEFT_ANGLE, movementArea);
        return 0;
    }
    return 0;
}


int main(int argc, char** argv){

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool done = false;

    std::cout << "Hello, from MyGame!\n";

    if (initialize(window, renderer) != 0) {
        return 1;
    } 

    Player::Player* player = new Player::Player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    World::World* world = new World::World(player, renderer);

    world->addEntity(player);

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            switch (event.type) {
                case SDL_EVENT_KEY_DOWN:
                    pressedKeyHandler(&event, player);
                    break;

                case SDL_EVENT_KEY_UP:
                    releasedKeyHandler(&event, player);
                    break;

            }
        }
        
        keyBoardPolling(player, world->getMovementArea()); 
        player->update(world->getMovementArea());
        world->update();
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        world->updateCamera(player);
        world->renderWorld(renderer);


        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player->getRenderbox());

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &player->getHitbox());

        // Moving Direction of Player
        #if DEBUG_MODE
            float rad = player->getMovingDirection().angle;
            float x1 = player->getPosition().x_onScreen + 60 * cos(rad);
            float y1 = player->getPosition().y_onScreen - 60 * sin(rad);
            SDL_RenderLine(renderer, (int)player->getPosition().x_onScreen,
                    (int)player->getPosition().y_onScreen, (int)x1, (int)y1);
        #endif

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }


    // Clean up
    delete player;
    delete world;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

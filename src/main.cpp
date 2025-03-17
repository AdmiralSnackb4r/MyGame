#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <player.hpp>
#include <world.hpp>
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
    switch (event->key.key) {  // Fixed: `key.keysym.sym` should be used
        case SDLK_W:
            std::cout << "Wee" << std::endl;
            break;
        case SDLK_D:
            player->walkTo(RIGHT_ANGLE);
            break;
        case SDLK_A:
            player->walkTo(LEFT_ANGLE);
            break;
        default:
            #ifdef DEBUG_MODE
            std::cerr << "Unhandled key press: " << SDL_GetKeyName(event->key.key) << std::endl;
            #endif
            break;
    }
    return 0;
}

int releasedKeyHandler(SDL_Event* event) {
#ifdef DEBUG_MODE
    std::cerr << "Key released: " << SDL_GetKeyName(event->key.key) << std::endl;
#endif
    return 0;
}

int eventHandler(SDL_Event* event, Player::Player* player) {

    const bool* keyState = SDL_GetKeyboardState(nullptr);

    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            return pressedKeyHandler(event, player);
        case SDL_EVENT_KEY_UP:
            return releasedKeyHandler(event);
        default:
            if (keyState[SDL_SCANCODE_D]) {
                player->walkTo(RIGHT_ANGLE);
                return 0;
            }
            if (keyState[SDL_SCANCODE_A]) {
                player->walkTo(LEFT_ANGLE);
                return 0;
            }
            return 0;
    }
}


int main(int argc, char** argv){

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool done = false;

    World::World* world = new World::World();
    Player::Player* player = new Player::Player(100, 100);

    std::cout << "Hello, from MyGame!\n";

    if (initialize(window, renderer) != 0) {
        return 1;
    } 

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            if (eventHandler(&event, player) != 0) {
                return 1;
            }
        }
        
        eventHandler(&event, player); 
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        world->renderWorld(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player->getHitbox());

        // Moving Direction of Player
        #ifdef DEBUG_MODE
            float rad = player->getMovingDirection().angle;
            float x1 = player->getPosition().x + 60 * cos(rad);
            float y1 = player->getPosition().y - 60 * sin(rad);
            SDL_RenderLine(renderer, (int)player->getPosition().x,
                    (int)player->getPosition().y, (int)x1, (int)y1);
        #endif

        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }


    // Clean up
    delete player;
    delete world;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <player.hpp>

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
        1000, // width in pixelsadd_subdirectory(thirdparty/SDL_ttf EXCLUDE_FROM_ALL)
        800, // height in pixels
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



int main(int argc, char** argv){

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool done = false;

    Player::Player* player = new Player::Player();

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
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player->getHitbox());

        SDL_RenderPresent(renderer);
    }


    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

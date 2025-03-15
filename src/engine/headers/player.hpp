#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

namespace Player {

    class Player {

        public:
            Player();
            ~Player();

            const SDL_FRect& getHitbox() const;

        private:
            const SDL_FRect mHitbox = { 100, 100, 50, 50}; // Hitbox properties
            std::vector<int> mActiveSprite = {0};


    };

} // namespace Player


#endif // PLAYER_H
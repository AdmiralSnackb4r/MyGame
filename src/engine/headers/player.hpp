#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

namespace Player {

    const int playerWidth = 50;
    const int playerHeight = 50;

    struct MovingDirection {
        float angle;
        float velocity;
        float acceleration;
    };

    struct Position {
        int x;
        int y;
    };

    class Player {

        public:
            Player(int x, int y);
            ~Player();

            const SDL_FRect& getHitbox() const;
            const MovingDirection getMovingDirection();
            const Position getPosition();

        private:
            SDL_FRect mHitbox; // Hitbox properties
            std::vector<int> mActiveSprite = {0};
            MovingDirection mMovingDirection;
            Position mPosition;


    };

} // namespace Player


#endif // PLAYER_H
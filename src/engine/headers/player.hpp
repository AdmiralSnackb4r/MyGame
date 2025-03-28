#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "config.h"

namespace Player {

    const int playerWidth = 50;
    const int playerHeight = 50;
    const float walkingSpeed = 5;

    struct MovingDirection {
        float angle;
        float velocityX;
        float accelerationX;

        float velocityY;
        float gravity;
        float jumpStrength;

    };

    struct Position {
        int x;
        int y;
        int w;
        int h;
    };

    struct Status {
        bool onGround;
    };


    class Player {

        public:
            Player(int x, int y);
            ~Player();



            const SDL_FRect& getHitbox() const;
            const MovingDirection getMovingDirection();
            const Position getPosition();
            const bool isOnGround();

            void setVelocity(float velocity);
            void setGround(bool onGround);

            void walkTo(float angle, const SDL_FRect* PlayerMovementArea);
            void jump();
            void update(const SDL_FRect* PlayerMovementArea);

        private:
            SDL_FRect mHitbox; // Hitbox properties
            std::vector<int> mActiveSprite = {0};

            MovingDirection mMovingDirection;
            Position mPosition;
            Status mStatus;

            void updateHitbox();


    };

} // namespace Player


#endif // PLAYER_H
#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

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

        float x_onScreen;
        float x_inWorld;
        float y_onScreen;
        float y_inWorld;
        
        float w;
        float h;
    };

    struct Status {
        bool onGround;
    };


    class Player {

        public:
            Player(int x, int y);
            ~Player();

            const SDL_FRect& getHitbox() const;
            const SDL_FRect& getRenderbox() const;
            const MovingDirection& getMovingDirection() const;
            const Position& getPosition() const;

            const bool isOnGround();

            void setVelocity(float velocity);
            void setGround(bool onGround);
            void setInWorldX(int x);
            void setInWorldY(int y);

            void walkTo(float angle, const SDL_FRect* PlayerMovementArea);
            void jump();
            void update(const SDL_FRect* PlayerMovementArea);

        private:
            SDL_FRect mHitbox;
            SDL_FRect mRenderbox;
            std::vector<int> mActiveSprite = {0};

            MovingDirection mMovingDirection;
            Position mPosition;
            Status mStatus;

            void updateHitbox();
            void updateRenderbox();


    };

} // namespace Player


#endif // PLAYER_H
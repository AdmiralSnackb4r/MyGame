#include "player.hpp"

Player::Player::Player(int x, int y) {
    #ifdef DEBUG_MODE
        std::cout << "Player object created" << std::endl;
    #endif

    mMovingDirection.angle = 0.0f;
    mMovingDirection.velocity = 0.0f;
    mMovingDirection.acceleration = 0.0f;

    mPosition.x = x;
    mPosition.y = y;

    mHitbox = {(x - static_cast<float>(playerWidth)/2),
               (y - static_cast<float>(playerHeight)/2),
                playerWidth, playerHeight};
}

Player::Player::~Player() {
    #ifdef DEBUG_MODE
        std::cout << "Player object deleted" << std::endl;
    #endif
}

const SDL_FRect& Player::Player::getHitbox() const {
    return mHitbox;
}

const Player::MovingDirection Player::Player::getMovingDirection() {
    return mMovingDirection;
}

const Player::Position Player::Player::getPosition() {
    return mPosition;
}

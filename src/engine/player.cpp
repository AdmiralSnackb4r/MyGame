#include "player.hpp"
#include <cmath>

Player::Player::Player(int x, int y) {
    #ifdef DEBUG_MODE
        std::cout << "Player object created" << std::endl;
    #endif

    mMovingDirection.angle = 0.0f;
    mMovingDirection.velocity = 0.0f;
    mMovingDirection.acceleration = 0.0f;

    mPosition.x = x;
    mPosition.y = y;

    mStatus.onGround = true;

    updateHitbox();

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

void Player::Player::walkTo(float angle) {
    if (mStatus.onGround) {
        mMovingDirection.angle = angle;
        mPosition.x = static_cast<int>(mPosition.x + (walkingSpeed * cos(angle)));
        updateHitbox();
    }
}

void Player::Player::updateHitbox() {
    mHitbox = {(mPosition.x - static_cast<float>(playerWidth)/2),
        (mPosition.y - static_cast<float>(playerHeight)/2),
         playerWidth, playerHeight};
}

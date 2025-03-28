#include "player.hpp"

Player::Player::Player(int x, int y) {
    #if DEBUG_MODE
        std::cout << "Player object created" << std::endl;
    #endif

    mPosition.x = x;
    mPosition.y = y;
    mPosition.w = 32;
    mPosition.h = 32;

    mStatus.onGround = true;


    mMovingDirection.angle = 0.0f;
    mMovingDirection.velocityX = 0.0f;
    mMovingDirection.accelerationX = 0.0f;
    mMovingDirection.gravity = 0.2f;
    mMovingDirection.jumpStrength = -10.0f;
    
    mMovingDirection.velocityY = 0.0f;


    updateHitbox();

}

Player::Player::~Player() {
    #if DEBUG_MODE
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

const bool Player::Player::isOnGround() {
    return mStatus.onGround;
}

void Player::Player::setVelocity(float velocity) {
    mMovingDirection.velocityX = velocity;
}

void Player::Player::setGround(bool onGround) {
    mStatus.onGround = onGround;
}

void Player::Player::walkTo(float angle, const SDL_FRect* PlayerMovementArea) {
    if (mStatus.onGround) {
        mMovingDirection.angle = angle;
        mMovingDirection.velocityX = walkingSpeed;
        int tmp_x = static_cast<int>(mPosition.x + (walkingSpeed * cos(angle)));
        if (tmp_x > PlayerMovementArea->x && tmp_x < (PlayerMovementArea->x + PlayerMovementArea->w)) {
            mPosition.x = tmp_x;
        }
    }
    updateHitbox();
}

void Player::Player::jump() {
    if (mStatus.onGround) {
        mMovingDirection.velocityY = mMovingDirection.jumpStrength;
        mStatus.onGround = false;
    }
}

void Player::Player::update(const SDL_FRect* PlayerMovementArea) {

    if (!mStatus.onGround) {
        int tmp_y = static_cast<int>(mPosition.y + mMovingDirection.velocityY);
        if (tmp_y > PlayerMovementArea->y && tmp_y < (PlayerMovementArea->y + PlayerMovementArea->h)) {
            mPosition.y += mMovingDirection.velocityY;
        }

        mMovingDirection.velocityY += mMovingDirection.gravity;
        mMovingDirection.velocityY = std::min(mMovingDirection.velocityY, VELOCITY_Y_MAX);

    } else {
        mMovingDirection.velocityY = 0.0f;
    }

    updateHitbox();

}

void Player::Player::updateHitbox() {
    mHitbox = {(mPosition.x - static_cast<float>(playerWidth)/2),
        (mPosition.y - static_cast<float>(playerHeight)/2),
         playerWidth, playerHeight};
}

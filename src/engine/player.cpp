#include "player.hpp"

namespace Player {

Player::Player(int x, int y) {
    #if DEBUG_MODE
        std::cout << "Player object created" << std::endl;
    #endif

    mPosition.x_inWorld = x;
    mPosition.x_onScreen = x;
    mPosition.y_inWorld = y;
    mPosition.y_onScreen = y;
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
    updateRenderbox();

}

Player::~Player() {
    #if DEBUG_MODE
        std::cout << "Player object deleted" << std::endl;
    #endif
}

const SDL_FRect& Player::getHitbox() const {
    return mHitbox;
}

const SDL_FRect &Player::getRenderbox() const {
    return mRenderbox;
}

const MovingDirection &Player::getMovingDirection() const {
    return mMovingDirection;
}

const Position &Player::getPosition() const {
    return mPosition;
}

const bool Player::isOnGround() {
    return mStatus.onGround;
}

void Player::setVelocity(float velocity) {
    mMovingDirection.velocityX = velocity;
}

void Player::setGround(bool onGround) {
    mStatus.onGround = onGround;
}

void Player::walkTo(float angle, const SDL_FRect* PlayerMovementArea) {
    if (mStatus.onGround) {
        mMovingDirection.angle = angle;
        mMovingDirection.velocityX = walkingSpeed;
        float cosAngle = cos(angle);
        int tmp_x_inWorld = static_cast<int>(mPosition.x_inWorld + (walkingSpeed * cosAngle));
        int tmp_x_onScreen = static_cast<int>(mPosition.x_onScreen + (walkingSpeed * cosAngle));
        if (tmp_x_onScreen > PlayerMovementArea->x && tmp_x_onScreen < (PlayerMovementArea->x + PlayerMovementArea->w)) {
            mPosition.x_onScreen = tmp_x_onScreen;
        }
        if (tmp_x_inWorld - mPosition.w > 0 && tmp_x_inWorld + mPosition.w < WORLD_WIDTH * TILE_SIZE) {
            mPosition.x_inWorld = tmp_x_inWorld;
        }
    }
    updateHitbox();
    updateRenderbox();
}

void Player::jump() {
    if (mStatus.onGround) {
        mMovingDirection.velocityY = mMovingDirection.jumpStrength;
        mStatus.onGround = false;
    }
}

void Player::update(const SDL_FRect* PlayerMovementArea) {

    if (!mStatus.onGround) {
        int tmp_y_inWorld = static_cast<int>(mPosition.y_inWorld + mMovingDirection.velocityY);
        int tmp_y_onScreen = static_cast<int>(mPosition.y_onScreen + mMovingDirection.velocityY);
        if (tmp_y_onScreen > PlayerMovementArea->y && tmp_y_onScreen < (PlayerMovementArea->y + PlayerMovementArea->h)) {
            mPosition.y_onScreen = tmp_y_onScreen;
        }
        if (tmp_y_inWorld - mPosition.h > 0 && tmp_y_inWorld + mPosition.h < (WORLD_HEIGHT * TILE_SIZE)) {
            mPosition.y_inWorld = tmp_y_inWorld;
        }

        mMovingDirection.velocityY += mMovingDirection.gravity;
        mMovingDirection.velocityY = std::min(mMovingDirection.velocityY, VELOCITY_Y_MAX);

    } else {
        mMovingDirection.velocityY = 0.0f;
    }

    updateHitbox();
    updateRenderbox();

}

void Player::updateHitbox() {
    mHitbox = {(mPosition.x_inWorld - static_cast<float>(mPosition.w)/2),
        (mPosition.y_inWorld - static_cast<float>(mPosition.h)/2),
         playerWidth, playerHeight};
}

void Player::updateRenderbox() {
    mRenderbox = {(mPosition.x_onScreen - static_cast<float>(mPosition.w)/2),
        (mPosition.y_onScreen - static_cast<float>(mPosition.h)/2),
         playerWidth, playerHeight};
}

}
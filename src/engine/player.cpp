#include "player.hpp"

namespace Player {

fs::path basePath = PROJECT_ROOT;
fs::path textures = "textures";
fs::path player = "player";
fs::path normal = "Player.bmp";
fs::path normalBMP = basePath / textures / player / normal;

Player::Player(int x, int y, SDL_Renderer* renderer) : mRenderRef{renderer} {

    #if DEBUG_MODE
        std::cout << "Player object created" << std::endl;
    #endif

    // Initialize hitbox properties
    mHitbox.x = x;
    mHitbox.y = y;
    mHitbox.w = 64;
    mHitbox.h = 128;

    // Initialize status properties
    mStatus.onGround = true;

    // Initialize movement properties
    mMovingDirection.angle = 0.0f;
    mMovingDirection.velocityX = 0.0f;
    mMovingDirection.accelerationX = 0.0f;
    mMovingDirection.gravity = 0.2f;
    mMovingDirection.jumpStrength = -10.0f;
    mMovingDirection.velocityY = 0.0f;

    // Load player texture
    mPlayerTextures[0] = textureUtils::loadTexture(normalBMP.string(), mRenderRef);

}

Player::~Player() {
    #if DEBUG_MODE
        std::cout << "Player object deleted" << std::endl;
    #endif
}

const SDL_FRect& Player::getHitbox() const {
    return mHitbox;
}

const MovingDirection &Player::getMovingDirection() const {
    return mMovingDirection;
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

void Player::setInWorldX(int x) {
    mHitbox.x = x;
}

void Player::setInWorldY(int y) {
    mHitbox.y = y;
}

void Player::walkTo(float angle) {

    if (!mStatus.onGround) return;

    // Update movement direction
    mMovingDirection.angle = angle;
    mMovingDirection.velocityX = WALKING_SPEED;

    // Calculate new X position
    int newX = static_cast<int>(mHitbox.x + (WALKING_SPEED * std::cos(angle)));

    // Keep the player within world boundaries
    if (newX > 0 && newX < WORLD_WIDTH * TILE_SIZE) {
        mHitbox.x = newX;
    }
}

void Player::jump() {

    if (!mStatus.onGround) return;

    // Apply jump force
    mMovingDirection.velocityY = mMovingDirection.jumpStrength;
    mStatus.onGround = false;
}

void Player::update() {

    if (mStatus.onGround) {
        mMovingDirection.velocityY = 0.0f;
        return;
    }

    // Calculate the new Y position
    int newY = static_cast<int>(mHitbox.y + mMovingDirection.velocityY);

    // Ensure the player stays within world boundaries
    if (newY > 0 && newY < (WORLD_HEIGHT * TILE_SIZE)) {
        mHitbox.y = newY;
    }

    // Apply gravity and limit velocity
    mMovingDirection.velocityY = std::min(mMovingDirection.velocityY + mMovingDirection.gravity, VELOCITY_Y_MAX);
}

void Player::renderPlayer(Camera::Camera *camera) {

    // Calculate the position of the player relative to the camera viewport
    SDL_FRect renderRect = {
        mHitbox.x - camera->getViewport().x,
        mHitbox.y - camera->getViewport().y,
        mHitbox.w, 
        mHitbox.h
    };

    // Render the player texture to the screen
    SDL_RenderTexture(mRenderRef, mPlayerTextures[mActiveSprite], nullptr, &renderRect);
}

}
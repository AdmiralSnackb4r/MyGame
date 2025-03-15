#include "player.hpp"

Player::Player::Player() {
    #ifdef DEBUG_MODE
        std::cout << "Player object created" << std::endl;
    #endif
}

Player::Player::~Player() {
    #ifdef DEBUG_MODE
        std::cout << "Player object deleted" << std::endl;
    #endif
}

const SDL_FRect& Player::Player::getHitbox() const {
    return mHitbox;
}

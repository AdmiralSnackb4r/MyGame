#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "textureUtils.hpp"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <filesystem>
#include <cmath>
#include "camera.hpp"

#define _USE_MATH_DEFINES


namespace Player {

    namespace fs = std::filesystem;

    // Player constants
    constexpr int PLAYER_WIDTH = 50;
    constexpr int PLAYER_HEIGHT = 50;
    constexpr float WALKING_SPEED = 5.0f;
    constexpr float AIR_MOVEMENT_SPEED = 2.5f;

    /**
     * @brief Struct representing player's movement properties.
     * @param angle Movement angle in radians <float> 
     * @param velocityX Horizontal velocity <float> 
     * @param accelerationX Horizontal acceleration <float> 
     * @param velocityY Vertical velocity <float> 
     * @param gravity Gravity force <float> 
     * @param jumpStrength Jump force <float> 
     */
    struct MovingDirection {
        float angle = 0.0f;             ///< Movement angle in radians
        float velocityX = 0.0f;         ///< Horizontal velocity
        float accelerationX = 0.0f;     ///< Horizontal acceleration

        float velocityY = 0.0f;         ///< Vertical velocity
        float gravity = 0.2f;           ///< Gravity force
        float jumpStrength = -10.0f;    ///< Jump force
    };

    /**
     * @brief Struct representing player's status 
     * @param onGround Whether the player is on the ground <bool>
     */
    struct Status {
        bool onGround = true; ///< Whether the player is on the ground
    };


    /**
     * @class Player
     * @brief Represents the player character in the game.
     */
    class Player {

        public:

            /**
             * @brief Constructor for Player.
             * @param x Initial x-position <int>
             * @param y Initial y-position <int>
             * @param renderer SDL Renderer reference <SDL_Renderer*>
             */
            Player(int x, int y, SDL_Renderer* renderer);

            /**
             * @brief Destructor for Player.
             */
            ~Player();

            // --- Setters ---
            
            /**
             * @param velocity <float>
             */
            void setVelocity(float velocity);

            /**
             * @param onGround <bool>
             */
            void setGround(bool onGround);

            /**
             * @param x <int>
             */
            void setInWorldX(int x);

            /**
             * @param y <int>
             */
            void setInWorldY(int y);


            void setMapRef(std::shared_ptr<std::vector<std::vector<int>>> mapRef);

            // --- Getters ---

            const SDL_FRect& getHitbox() const;
            const MovingDirection& getMovingDirection() const;
            const bool isOnGround();


            // --- Player Actions ---

            /**
             * @brief Moves the player in a specified direction.
             * @param angle Direction angle in radians <float>
             */
            void walkTo(float angle);

            /**
             * @brief Makes the player jump.
             */
            void jump();

            /**
             * @brief Updates the player with respect to physics [gravity].
             */
            void update();


            bool isColliding(int x, int y);

            // --- Rendering ---
            
            /**
             * @brief Renders the player sprite on the screen.
             * @param camera Camera reference <Camera*>
             */
            void renderPlayer(Camera::Camera* camera);

        private:
            SDL_Texture* mPlayerTextures[1] = {nullptr}; ///< Player textures array (single sprite for now)
            int mActiveSprite = 0; ///< Active sprite index
            SDL_Renderer* mRenderRef = nullptr; ///< SDL Renderer reference
            std::shared_ptr<std::vector<std::vector<int>>> mMapRef = {nullptr};
            SDL_FRect mHitbox{}; ///< Player hitbox
            MovingDirection mMovingDirection{}; ///< Movement properties
            Status mStatus{}; ///< Player's status

    };

} // namespace Player


#endif // PLAYER_H
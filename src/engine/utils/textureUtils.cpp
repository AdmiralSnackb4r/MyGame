#include "textureUtils.hpp"
#include <SDL3/SDL.h>
#include <iostream>

namespace textureUtils {


SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {

    // Load the image surface from the given path
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        SDL_Log("Error loading texture from path '%s': %s", path.c_str(), SDL_GetError());
        return nullptr;  // Return nullptr if loading the surface fails
    }

    // Create a texture from the loaded surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Error creating texture from surface for path '%s': %s", path.c_str(), SDL_GetError());
    }

    // Clean up the surface after texture creation
    SDL_DestroySurface(surface);

    return texture;  // Return the texture (nullptr if creation failed)
}






};
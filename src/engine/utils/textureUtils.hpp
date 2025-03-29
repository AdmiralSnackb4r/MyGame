#ifndef TEXTURE_UTILS
#define TEXTURE_UTILS

#include <SDL3/SDL.h>
#include <iostream>

namespace textureUtils {


/**
 * @brief Loads a texture from a file.
 * @param path Path to the texture file.
 * @return Pointer to the loaded SDL_Texture.
 */
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

};
#endif // TEXTURE_UTILS
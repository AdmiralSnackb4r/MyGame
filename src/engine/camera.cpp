#include "camera.hpp"

Camera::Camera::Camera(int w, int h) {
    viewport = {1, 1, w, h};
}

SDL_Rect Camera::Camera::getViewport() {
    return viewport;
}

void Camera::Camera::update(const SDL_FRect &playerRect)
{
    viewport.x = playerRect.x + playerRect.w / 2 - viewport.w / 2;
    viewport.y = playerRect.y + playerRect.h / 2 - viewport.h / 2;
}

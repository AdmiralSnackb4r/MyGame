#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>
#include <vector>

namespace Camera {

class Camera {

    public:
        Camera(int w, int h);
        ~Camera() = default;

        SDL_Rect getViewport();

        void update(const SDL_FRect& playerRect);


    private:
        SDL_Rect viewport;
        int screenWidth, screenHeight;


};

}

#endif // CAMERA_H
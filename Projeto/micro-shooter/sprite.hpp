#ifndef sprite_hpp
#define sprite_hpp

#include "SDL.h"
#include <string>

class Sprite {
private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    int frameWidth, frameHeight;
    int currentFrame, totalFrames;
    float frameTime, currentFrameTime;

public:
    Sprite(const std::string& filePath, SDL_Renderer* renderer, int frameWidth, int frameHeight, int totalFrames, float frameTime);
    ~Sprite();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int x, int y);
};

#endif
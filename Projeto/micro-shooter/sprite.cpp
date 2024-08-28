#include "sprite.hpp"
#include "SDL_image.h"

Sprite::Sprite(const std::string& filePath, SDL_Renderer* renderer, int frameWidth, int frameHeight, int totalFrames, float frameTime)
    : frameWidth(frameWidth), frameHeight(frameHeight), totalFrames(totalFrames), frameTime(frameTime), currentFrame(0), currentFrameTime(0.0f) {
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    srcRect = { 0, 0, frameWidth, frameHeight };
    destRect = { 0, 0, frameWidth, frameHeight };
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::update(float deltaTime) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= frameTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        srcRect.x = currentFrame * frameWidth;
        currentFrameTime = 0.0f;
    }
}

void Sprite::render(SDL_Renderer* renderer, int x, int y, int width, int height) {
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
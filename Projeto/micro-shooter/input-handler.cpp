#include "game.hpp"
#include "player.hpp"
void handleInput(Game* game) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys != nullptr) {
        if (keys[SDL_SCANCODE_LEFT]) {
            game->player.moveLeft(game->frameTime);
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            game->player.moveRight(game->frameTime);
        }
        if (keys[SDL_SCANCODE_UP]) {
            game->player.moveUp(game->frameTime);
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            game->player.moveDown(game->frameTime);
        }
        if (keys[SDL_SCANCODE_Z]) {
        }
    }
}

#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"

Game::Game()
{
    const Color backgroundColor = { 0, 0, 255, 255 };
    const Color playerColor = { 0, 255, 0, 255 };
    Rect playerRect = { Vector(300, 300), 40, 40 };

    graphicInterface = new GraphicImplementSdl();
    eventInterface = new EventImplementSdl();
    eventInterface->setIsRunning(true);
    FPS = 60.0f;
    frameDelay = 1000.0f / FPS;
    frameTime = 0;

    // Inicialize o estado do teclado
    keys = SDL_GetKeyboardState(NULL);

    while (eventInterface->getIsRunning()) {
        frameStart = SDL_GetTicks();
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        // Atualize o estado do jogador
        eventInterface->handleEvents();

        // Verifique se as teclas foram pressionadas
        if (keys != nullptr) {
            if (keys[SDL_SCANCODE_LEFT]) {
                playerRect.position.x -= player.getSpeed().x * frameTime;
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                playerRect.position.x += player.getSpeed().x * frameTime;
            }
            if (keys[SDL_SCANCODE_UP]) {
                playerRect.position.y -= player.getSpeed().y * frameTime;
            }
            if (keys[SDL_SCANCODE_DOWN]) {
                playerRect.position.y += player.getSpeed().y * frameTime;
            }
        }

        // Limpe a tela
        graphicInterface->clearRender(backgroundColor);

        // Defina a posição do retângulo do jogador
        player.setRect(playerRect);

        // Desenhe o jogador na tela com a nova posição
        graphicInterface->drawRect(player.getRect(), playerColor);

        // Atualize a renderização
        graphicInterface->updateRender();

        frameTime = static_cast<float>(SDL_GetTicks() - frameStart) / 1000.0f;
    }

    graphicInterface->cleanWindow();
}

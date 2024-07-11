#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"

Game::Game()
{
    const Color backgroundColor = {0, 0, 255, 255};
    const Color playerColor = {0, 255, 0, 255};
    const Color bulletColor = {255, 255, 255, 255};
    Rect playerRect = {Vector(300, 300), 40, 40};

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
                player.moveLeft(frameTime);
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                player.moveRight(frameTime);
            }
            if (keys[SDL_SCANCODE_UP]) {
                player.moveUp(frameTime);
            }
            if (keys[SDL_SCANCODE_DOWN]) {
                player.moveDown(frameTime);
            }
            if (keys[SDL_SCANCODE_Z]) {
                shootBullet();
            }
        }


        for (auto& bullet : bullets) {
            bullet->moveUp(); // Ou a direção desejada
            // Desenhe a bala
            Rect bulletRect = {bullet->getPosition(), bullet->getWidth(), bullet->getHeight()};
            graphicInterface->drawRect(bulletRect, bulletColor); // Defina bulletColor conforme necessário
            graphicInterface->updateRender(); // Atualize a renderização após desenhar a bala
        }

auto bulletRemover = [](Bullet* b) -> bool {
    if (b->getPosition().y < 0) {
        delete b; // Libera a memória da bala
        return true; // Marca para remoção da lista
    }
    return false;
};
bullets.remove_if(bulletRemover);

        // Limpe a tela
        graphicInterface->clearRender(backgroundColor);

        // Defina a posi��o do ret�ngulo do jogador
        playerRect = {player.getPosition(), 40, 40};

        // Desenhe o jogador na tela com a nova posi��o
        graphicInterface->drawRect(playerRect, playerColor);

        // Atualize a renderiza��o
        graphicInterface->updateRender();

        frameTime = static_cast<float>(SDL_GetTicks() - frameStart) / 1000.0f;
    }

    graphicInterface->cleanWindow();
}

void Game::shootBullet() {
    Vector playerPos = player.getPosition();
    Bullet* newBullet = new Bullet(playerPos + Vector(player.getWidth() / 2, 0)); // Ajuste a posição inicial conforme necessário
    bullets.push_back(newBullet);
}

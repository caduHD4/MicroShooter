#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"
#include "sdl_mixer.h"
#include <cmath>

Game::Game() {
    int init = Mix_Init(0);
    // fundo, tela, jogador e balas
    const Color backgroundColor = { 0, 0, 255, 255 };
    const Color playerColor = { 0, 255, 0, 255 };
    const Color bulletColor = { 255, 255, 255, 255 };
    // Instancia as classes gráficas de uma classe generica
    graphicInterface = new GraphicImplementSdl();
    eventInterface = new EventImplementSdl();
    eventInterface->setIsRunning(true);
    // Lida com o framerate
    FPS = 60.0f;
    frameDelay = 1000.0f / FPS;
    frameTime = 0;
    // Detectação das teclas
    keys = SDL_GetKeyboardState(NULL);
    Uint32 lastUpdateTick = SDL_GetTicks();
    // Delay da bala
    lastShotTime = 0;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    for (int i = 0; i < 5; ++i) { //5 inimigos
        Enemy enemy;
        enemy.setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
        enemies.push_back(enemy);
    }


    // Looping principal do jogo
    while (eventInterface->getIsRunning()) {
        frameStart = SDL_GetTicks();

        eventInterface->handleEvents();
        float SecsBetweenUpdate = (SDL_GetTicks() - lastUpdateTick) / 1000.0f;
        this->update(SecsBetweenUpdate);
        lastUpdateTick = SDL_GetTicks();

        this->render();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay >= frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        else {

        }
    }

    graphicInterface->cleanWindow();
}


void Game::update(float deltaTime) {
    if (keys != nullptr) {
        if (keys[SDL_SCANCODE_LEFT]) {
            player.moveLeft(deltaTime);
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            player.moveRight(deltaTime);
        }
        if (keys[SDL_SCANCODE_UP]) {
            player.moveUp(deltaTime);
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            player.moveDown(deltaTime);
        }
        if (keys[SDL_SCANCODE_Z]) {
            shootBullet();
        }
    }

    // Atualiza a posição das balas
    for (auto& bullet : bullets) {
        bullet->move(deltaTime);
    }


    for (auto& enemy : enemies) {
        // Lógica de movimentação do inimigo
        enemy.move(deltaTime);

        // Lógica de colisão com balas
        for (auto bullet : bullets) {
            if (bullet->getPosition().x < enemy.getPosition().x + enemy.getWidth() &&
                bullet->getPosition().x + bullet->getWidth() > enemy.getPosition().x &&
                bullet->getPosition().y < enemy.getPosition().y + enemy.getHeight() &&
                bullet->getPosition().y + bullet->getHeight() > enemy.getPosition().y) {
                std::cout << "Colisao com a bala!" << std::endl;
                enemy.setLife(enemy.getLife() - 1);
                if (enemy.getLife() <= 0) {
                    std::cout << "Inimigo destruido!" << std::endl;
                    Mix_Chunk* enemyFaintedEffect = Mix_LoadWAV("audio/enemy-fainted.wav");
                    Mix_PlayChannel(-1, enemyFaintedEffect, 0);
                    enemy.setDead(true); 
                }
                bullet->setLife(0);
            }
        }
    }

    auto enemyRemover = [](Enemy& e) -> bool {
        return e.isDead();
        };
    enemies.remove_if(enemyRemover);

    // Remover balas fora da tela e quando a vida da bala chega a 0
    auto bulletRemover = [](Bullet* b) -> bool {
        if (b->getPosition().y < 0 || b->getLife() <= 0) {
            delete b;
            return true;
        }
        return false;
        };
    bullets.remove_if(bulletRemover);
}

void Game::render() {
    const Color backgroundColor = { 0, 0, 255, 255 };
    const Color playerColor = { 0, 255, 0, 255 };
    const Color bulletColor = { 255, 255, 255, 255 };
    const Color enemyColor = { 255, 0, 0, 255 };

    graphicInterface->clearRender(backgroundColor);

    Rect playerRect = { player.getPosition(), player.getWidth(), player.getHeight() };
    graphicInterface->drawRect(playerRect, playerColor);

    for (auto& bullet : bullets) {
        Rect bulletRect = { bullet->getPosition(), bullet->getWidth(), bullet->getHeight() };
        graphicInterface->drawRect(bulletRect, bulletColor);
    }

    for (auto& enemy : enemies) {
        Rect enemyRect = { enemy.getPosition(), enemy.getWidth(), enemy.getHeight() };
        graphicInterface->drawRect(enemyRect, enemyColor);
        enemy.drawHealthBar(graphicInterface);
    }

    graphicInterface->updateRender();
}

void Game::shootBullet() {
    Uint32 currentTime = SDL_GetTicks();
    // cooldown entre tiros
    Mix_Chunk* shootEffect = Mix_LoadWAV("audio/shoot.wav");
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = player.getPosition();
        Bullet* newBullet = new Bullet(playerPos + Vector(player.getWidth() / 3, 0));
        Mix_PlayChannel(-1, shootEffect, 0);
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do último disparo
    }
}
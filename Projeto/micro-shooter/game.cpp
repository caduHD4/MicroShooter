#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"

Game::Game() {
    const Color backgroundColor = { 0, 0, 255, 255 };
    const Color playerColor = { 0, 255, 0, 255 };
    const Color bulletColor = { 255, 255, 255, 255 };
    Rect playerRect = { Vector(300, 300), 40, 40 };
    graphicInterface = new GraphicImplementSdl();
    eventInterface = new EventImplementSdl();
    eventInterface->setIsRunning(true);
    FPS = 60.0f;
    frameDelay = 1000.0f / FPS;
    frameTime = 0;
    keys = SDL_GetKeyboardState(NULL);
    Uint32 lastUpdateTick = SDL_GetTicks();
    lastShotTime = 0;

    // Spawna o inimigo a 200 pixels do jogador
    Vector enemyPosition = player.getPosition() + Vector(200, 0);
    enemy.setPosition(enemyPosition);

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
            // TODO: Tratar lag
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

    for (auto& bullet : bullets) {
        bullet->moveUp();
    }


    if (player.getPosition().x < enemy.getPosition().x + enemy.getWidth() &&
        player.getPosition().x + player.getWidth() > enemy.getPosition().x &&
        player.getPosition().y < enemy.getPosition().y + enemy.getHeight() &&
        player.getPosition().y + player.getHeight() > enemy.getPosition().y) {
        std::cout << "Colisão com o jogador!" << std::endl;

        enemy.setLife(enemy.getLife() - 1);
    }


    bool collisionDetected = false;
    for (auto& bullet : bullets) {
        if (bullet->getPosition().x < enemy.getPosition().x + enemy.getWidth() &&
            bullet->getPosition().x + bullet->getWidth() > enemy.getPosition().x &&
            bullet->getPosition().y < enemy.getPosition().y + enemy.getHeight() &&
            bullet->getPosition().y + bullet->getHeight() > enemy.getPosition().y) {
            if (!collisionDetected) {
                std::cout << "Colisão com a bala!" << std::endl;
                collisionDetected = true;
            }

            enemy.setLife(enemy.getLife() - 1);
        }
    }

    // Remove o inimigo se a vida chegar a 0
    if (enemy.getLife() <= 0) {
        static bool enemyDestroyed = false;
        if (!enemyDestroyed) {
            std::cout << "Inimigo destruído!" << std::endl;
            enemyDestroyed = true;
        }
        // Remove o inimigo da tela
        enemy.setPosition(Vector(-100, -100));
    }
    auto bulletRemover = [](Bullet* b) -> bool {
        if (b->getPosition().y < 0) {
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

    Rect playerRect = { player.getPosition(), 40, 40 };
    graphicInterface->drawRect(playerRect, playerColor);

    for (auto& bullet : bullets) {
        Rect bulletRect = { bullet->getPosition(), bullet->getWidth(), bullet->getHeight() };
        graphicInterface->drawRect(bulletRect, bulletColor);
    }

    Rect enemyRect = { enemy.getPosition(), enemy.getWidth(), enemy.getHeight() };
    graphicInterface->drawRect(enemyRect, enemyColor);

    graphicInterface->updateRender();
}

void Game::shootBullet() {
    Uint32 currentTime = SDL_GetTicks();
	//cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = player.getPosition();
        Bullet* newBullet = new Bullet(playerPos + Vector(player.getWidth() / 81, -34));
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do último disparo
    }
}
#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"

Game::Game() {
	// fundo, tela, jogador e balas
    const Color backgroundColor = { 0, 0, 255, 255 };
    const Color playerColor = { 0, 255, 0, 255 };
    const Color bulletColor = { 255, 255, 255, 255 };
    //Instancia as classes gráficas de uma classe generica
    graphicInterface = new GraphicImplementSdl();
    eventInterface = new EventImplementSdl();
    eventInterface->setIsRunning(true);
    //Lida com o framerate
    FPS = 60.0f;
    frameDelay = 1000.0f / FPS;
    frameTime = 0;
    // Detectação das teclas
    keys = SDL_GetKeyboardState(NULL);
    Uint32 lastUpdateTick = SDL_GetTicks();
    // Delay da bala
    lastShotTime = 0;

    // Spawna o inimigo a 200 pixels do jogador
    Vector enemyPosition = player.getPosition() + Vector(200, 0);
    enemy.setPosition(enemyPosition);

	//Looping principal do jogo
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

// Move o jogador e as balas
void Game::update(float deltaTime) {
    if (keys != nullptr) {
        if (keys[SDL_SCANCODE_LEFT]) {
			player.move(-1.0f, 0.0f, deltaTime); // Esquerda
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
			player.move(1.0f, 0.0f, deltaTime); // Direita
        }
        if (keys[SDL_SCANCODE_UP]) {
            player.move(0.0f, -1.0f, deltaTime); // Cima
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            player.move(0.0f, 1.0f, deltaTime); // Baixo
        }
        if (keys[SDL_SCANCODE_Z]) {
            shootBullet();
        }
    }

    // Atualiza a posição das balas
    for (auto& bullet : bullets) {
        bullet->move(0.0f, 1.0f, deltaTime);
    }

	// Colisão do jogador com o inimigo
    if (player.getPosition().x < enemy.getPosition().x + enemy.getWidth() &&
        player.getPosition().x + player.getWidth() > enemy.getPosition().x &&
        player.getPosition().y < enemy.getPosition().y + enemy.getHeight() &&
        player.getPosition().y + player.getHeight() > enemy.getPosition().y) {
        std::cout << "Colisão com o jogador!" << std::endl;

        enemy.setLife(enemy.getLife() - 1);
    }

	// Colisão da bala com o inimigo
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

// Renderiza o jogador, as balas e o inimigo
void Game::render() {
    const Color backgroundColor = { 0, 0, 255, 255 };
    const Color playerColor = { 0, 255, 0, 255 };
    const Color bulletColor = { 255, 255, 255, 255 };
    const Color enemyColor = { 255, 0, 0, 255 };

    graphicInterface->clearRender(backgroundColor);

    Rect playerRect = { player.getPosition(), player.getWidth(), player.getHeight()};
    graphicInterface->drawRect(playerRect, playerColor);

    for (auto& bullet : bullets) {
        Rect bulletRect = { bullet->getPosition(), bullet->getWidth(), bullet->getHeight() };
        graphicInterface->drawRect(bulletRect, bulletColor);
    }

    Rect enemyRect = { enemy.getPosition(), enemy.getWidth(), enemy.getHeight() };
    graphicInterface->drawRect(enemyRect, enemyColor);

    graphicInterface->updateRender();
}

// Cria uma bala, tiro powwwww, powwww
void Game::shootBullet() {
    Uint32 currentTime = SDL_GetTicks();
	//cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = player.getPosition();
        Bullet* newBullet = new Bullet(playerPos + Vector(player.getWidth() / 3, 0));
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do último disparo
    }
}
#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"
#include "sdl_mixer.h"
#include <SDL_ttf.h>
#include <cmath>
#include <SDL_image.h>

Game::Game() : isFrozen(false) {
    int init = Mix_Init(0);
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
    }
    // Instancia as classes gráficas de uma classe generica
    graphicInterface = new GraphicImplementSdl();
    eventInterface = new EventImplementSdl();
    player = new Player(graphicInterface->getSdlRenderer());
	eventInterface->setPlayer(player);
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
    lastSpawnTime = 0;

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(16);

    shootEffect = Mix_LoadWAV("audio/shoot.wav");
    enemyDestroyedEffect = Mix_LoadWAV("audio/enemy-fainted.wav");


    // Carrega a música de fundo
    Mix_Music* backgroundMusic = Mix_LoadMUS("audio/theme.wav");
    if (backgroundMusic == nullptr) {
        std::cerr << "Erro ao carregar a música de fundo: " << Mix_GetError() << std::endl;
    }
    else {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    for (int i = 0; i < 5; ++i) { // 5 inimigos iniciais
        Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
        enemy->setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
        enemies.push_back(enemy);
    }

    SDL_Surface* tempSurface = IMG_Load("sprite/teste.png");
    if (tempSurface == nullptr) {
        std::cerr << "Erro ao carregar a imagem de fundo: " << IMG_GetError() << std::endl;
    }
    else {
        backgroundTexture = SDL_CreateTextureFromSurface(graphicInterface->getSdlRenderer(), tempSurface);
        SDL_FreeSurface(tempSurface);
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

Game::~Game() {
    Mix_FreeChunk(shootEffect); // Libera a memória
    Mix_CloseAudio();
    SDL_DestroyTexture(backgroundTexture);
    IMG_Quit();
    delete graphicInterface;
    delete eventInterface;
    delete player;
}

void Game::update(float deltaTime) {

    if (keys != nullptr && keys[SDL_SCANCODE_C]) {
        resetGame();
        return;
    }

    if (isFrozen==true) {
        return;
    }

    if (keys != nullptr) {
        if (keys[SDL_SCANCODE_Z]) {
            shootBullet();
        }
        if (keys[SDL_SCANCODE_X]) {
            spawnEnemies();
        }
        if (keys[SDL_SCANCODE_LEFT]) {
            player->moveLeft(deltaTime);
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            player->moveRight(deltaTime);
        }
        if (keys[SDL_SCANCODE_UP]) {
            player->moveUp(deltaTime);
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            player->moveDown(deltaTime);
        }
    }

    player->update(deltaTime);

    for (auto& enemy : enemies) {
        enemy->update(deltaTime);
    }

    // Atualiza a posição das balas
    for (auto& bullet : bullets) {
        bullet->move(deltaTime);
        bullet->update(deltaTime);
    }


    for (auto& enemy : enemies) {
        // Lógica de movimentação do inimigo
        enemy->move(deltaTime);

        // Lógica de colisão com balas
        for (auto bullet : bullets) {
            if (SDL_HasIntersection(&bullet->getHitbox(), &enemy->getHitbox())) {
                std::cout << "Colisao com a bala!" << std::endl;
                enemy->setLife(enemy->getLife() - 1);
                if (enemy->getLife() <= 0) {
                    std::cout << "Inimigo destruido!" << std::endl;
                    player->updateScore(enemy->getPoints());
                    std::cout << "Pontuacao: " << player->getScore() << std::endl;
                    int channel = Mix_PlayChannel(-1, enemyDestroyedEffect, 0);
                    enemy->setDead(true);
                }
                bullet->setLife(0);
            }
        }

        if (SDL_HasIntersection(&player->getHitbox(), &enemy->getHitbox())) {
            std::cout << "Colisao com o inimigo!" << std::endl;
            player->setLife(player->getLife() - 1);
            if (player->getLife() <= 0) {
                std::cout << "Player destruido!" << std::endl;
                player->setDead(true);
                isFrozen = true;
            }
        }
    }

    enemies.remove_if([](Enemy* enemy) {
        if (enemy->isDead()) {
            delete enemy;
            return true;
        }
        return false;
    });

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
    Color backgroundColor = { 0, 0, 255, 255 };
    const Color bulletColor = { 255, 255, 255, 255 };
    const Color enemyColor = { 255, 0, 0, 255 };

    if (isFrozen) {
        backgroundColor = { 255, 0, 0, 255 }; // Muda a cor de fundo para vermelho
    }

    if (player->isDead()) {
        showGameOverScreen();
        return;
    }

    graphicInterface->clearRender(backgroundColor);

    // Renderiza a textura do background
    SDL_RenderCopy(graphicInterface->getSdlRenderer(), backgroundTexture, NULL, NULL);

    player->render(graphicInterface->getSdlRenderer());
    player->renderHitbox(graphicInterface->getSdlRenderer());
    player->createHealthBar(graphicInterface);
    player->createEnergyBar(graphicInterface);
    graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(600, 7), { 255, 255, 255, 255 });

    for (auto& bullet : bullets) {
        bullet->render(graphicInterface->getSdlRenderer());
        bullet->renderHitbox(graphicInterface->getSdlRenderer());
    }

    for (auto& enemy : enemies) {
        enemy->render(graphicInterface->getSdlRenderer());
        enemy->createHealthBar(graphicInterface);
        enemy->renderHitbox(graphicInterface->getSdlRenderer());
    }

    graphicInterface->updateRender();
}

void Game::shootBullet() {
    Uint32 currentTime = SDL_GetTicks();
    // cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = player->getPosition();
        Bullet* newBullet = new Bullet(playerPos + Vector(player->getWidth() / 4, -30), graphicInterface->getSdlRenderer());
        int channel = Mix_PlayChannel(-1, shootEffect, 0);
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do último disparo
    }
}

//spawn de inimigos para testes
void Game::spawnEnemies() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime >= enemiesCooldown) {
        lastSpawnTime = currentTime;
        for (int i = 0; i < 5; ++i) { // 5 inimigos iniciais
            Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
            enemy->setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
            enemies.push_back(enemy);
        }
    }
}

void Game::showGameOverScreen() {

    graphicInterface->clearRender({ 0, 0, 0, 255 });

    // Renderiza o texto "Game Over"
    // Supondo que você tenha uma função para renderizar texto
    graphicInterface->drawText("Game Over", Vector(310, 300), { 255, 255, 255, 255 }); // Texto branco no centro da tela
    graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(310, 350), { 255, 255, 255, 255 }); // Texto branco no centro da tela

    graphicInterface->updateRender();
}

void Game::resetGame() {
    for (auto& enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    for (auto& bullet : bullets) {
        delete bullet;
    }
    bullets.clear();


    player->setPosition(Vector(400, 400)); 
    player->setLife(3);
    player->setDead(false);
    player->setScore(0);

    for (int i = 0; i < 5; ++i) { 
        Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
        enemy->setPosition(Vector(100 * i, 100 + 50 * i));
        enemies.push_back(enemy);
    }

    isFrozen = false;
    lastShotTime = 0;
    lastSpawnTime = 0;
}
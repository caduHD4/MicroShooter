#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"
#include "sdl_mixer.h"
#include <SDL_ttf.h>
#include <cmath>
#include <SDL_image.h>
#include "chrono"

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
    lastSpawnTime = 0;

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(16);

    enemyDestroyedEffect = Mix_LoadWAV("audio/enemy-fainted.wav");

    // Carrega a música de fundo
    Mix_Music* backgroundMusic = Mix_LoadMUS("audio/theme.wav");
    if (backgroundMusic == nullptr) {
        std::cerr << "Erro ao carregar a música de fundo: " << Mix_GetError() << std::endl;
    }
    else {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    for (int i = 0; i < 4; ++i) { // 5 inimigos iniciais
        Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
        enemy->setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
        enemies.push_back(enemy);
    }

    SDL_Surface* tempSurface = IMG_Load("sprite/back.jpg");
    if (tempSurface == nullptr) {
        std::cerr << "Erro ao carregar a imagem de fundo: " << IMG_GetError() << std::endl;
    }
    else {
        backgroundTexture = SDL_CreateTextureFromSurface(graphicInterface->getSdlRenderer(), tempSurface);
        SDL_FreeSurface(tempSurface);
    }

    auto fourseconds = std::chrono::system_clock::now() + std::chrono::milliseconds(4000);
    // Looping principal do jogo
    while (eventInterface->getIsRunning()) {
        if (fourseconds <= std::chrono::system_clock::now()) {
            for (int i = 0; i < 4; ++i) { // 5 inimigos iniciais
                Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
                enemy->setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
                enemies.push_back(enemy);
            }
            fourseconds = std::chrono::system_clock::now() + std::chrono::milliseconds(4000);
        }
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

    if (player->getLife() <= 0) {
        std::cout << "Player destruido!" << std::endl;
        player->setDead(true);
        isFrozen = true;
    }

    if (keys != nullptr && keys[SDL_SCANCODE_C]) {
        resetGame();
        return;
    }

    if (isFrozen==true) {
        return;
    }

    if (keys != nullptr) {
        player->limiteTela(deltaTime);
        if (keys[SDL_SCANCODE_Z]) {
            player->shootBullet(graphicInterface, deltaTime);
        }
        /*if (keys[SDL_SCANCODE_X]) {
            spawnEnemies();
        }*/
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

    for (auto& bullet : player->getBullets()) {
        bullet->move(frameTime);
        bullet->update(frameTime);
    }

     for (auto& enemy : enemies) {
        enemy->shootBulletRemoteGuided(player, graphicInterface, deltaTime);
        enemy->update(deltaTime);

        for (auto& bullet : enemy->getBullets()) {
            if (bullet->getIsRemoteGuided()) {
                bullet->moveRemoteGuided(player, frameTime);
            } else {
                bullet->move(frameTime);
            }
            bullet->update(frameTime);
        }

        for (auto bullet : enemy->getBullets()) {
            if (SDL_HasIntersection(&bullet->getHitbox(), &player->getHitbox())) {
                player->takeDamage(1);
                bullet->setLife(0);
            }
        }

        // Lógica de movimentação do inimigo
        enemy->move(deltaTime);

        // Lógica de colisão com balas
        player->bulletCollision(enemy, enemyDestroyedEffect);

        if (SDL_HasIntersection(&player->getHitbox(), &enemy->getHitbox())) {
            std::cout << "Colisao com o inimigo!" << std::endl;
            player->takeDamage(1);
            if (player->getLife() <= 0) {
                std::cout << "Player destruido!" << std::endl;
                isFrozen = true;
            }
        }

        enemy->removeBullets();
    }

    enemies.remove_if([this](Enemy* enemy) {
        if (enemy->isDead()) {
            for (auto& bullet : enemy->getBullets()) {
                remainingBullets.push_back(bullet);
            }
            delete enemy;
            return true;
        }
        return false;
    });

    player->removeBullets();

    // Atualize as balas restantes
    for (auto& bullet : remainingBullets) {
        bullet->move(frameTime);
        bullet->update(frameTime);
    }
    remainingBullets.remove_if([](Bullet* bullet) {
        if (bullet->getPosition().y > 1080 || bullet->getLife() <= 0) {
            delete bullet;
            return true;
        }
        return false;
    });
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
    SDL_Rect destRect = { 0, 0, 1920, 1080 }; // Ajuste conforme a resolução da sua tela
    SDL_RenderCopy(graphicInterface->getSdlRenderer(), backgroundTexture, NULL, &destRect);

    player->render(graphicInterface->getSdlRenderer());
    //player->renderHitbox(graphicInterface->getSdlRenderer());
    player->createHealthBar(graphicInterface);
    //player->createEnergyBar(graphicInterface);
    graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(1750, 7), { 255, 255, 255, 255 });

    for (auto& bullet : player->getBullets()) {
        bullet->render(graphicInterface->getSdlRenderer());
        //bullet->renderHitbox(graphicInterface->getSdlRenderer());
    }

    for (auto& enemy : enemies) {
        for (auto& bullet : enemy->getBullets()) {
            bullet->render(graphicInterface->getSdlRenderer());
        }
        enemy->render(graphicInterface->getSdlRenderer());
        enemy->createHealthBar(graphicInterface);
        //enemy->renderHitbox(graphicInterface->getSdlRenderer());
    }

        // Renderize as balas restantes
    for (auto& bullet : remainingBullets) {
        bullet->render(graphicInterface->getSdlRenderer());
    }

    graphicInterface->updateRender();
}

//spawn de inimigos para testes
void Game::spawnEnemies() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime >= enemiesCooldown) {
        lastSpawnTime = currentTime;
        for (int i = 0; i < 2; ++i) { // 5 inimigos iniciais
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
    graphicInterface->drawText("Game Over", Vector(880, 480), { 255, 255, 255, 255 }); // Texto branco no centro da tela
    graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(880, 520), { 255, 255, 255, 255 }); // Texto branco no centro da tela

    graphicInterface->updateRender();
}

void Game::resetGame() {
    for (auto& enemy : enemies) {
        for (auto& bullet : enemy->getBullets()) {
            delete bullet;
        }
        enemy->getBullets().clear();
    }

    for (auto& enemy : enemies) {
        delete enemy;
    }

    enemies.clear();

    for (auto& bullet : player->getBullets()) {
        delete bullet;
    }
    player->getBullets().clear();

    player = new Player(graphicInterface->getSdlRenderer());
    for (int i = 0; i < 4; ++i) { // 5 inimigos iniciais
        Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
        enemy->setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
        enemies.push_back(enemy);
    }

    isFrozen = false;
    lastSpawnTime = 0;
}
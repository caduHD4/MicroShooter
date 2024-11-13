#include "game.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"
#include "bullet.hpp"
#include "sdl_mixer.h"
#include <SDL_ttf.h>
#include <cmath>
#include <SDL_image.h>
#include "chrono"
#include <fstream>

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
    showStartMenu();

    enemyDestroyedEffect = Mix_LoadWAV("audio/enemy-fainted.wav");

    // Carrega a música de fundo
    Mix_Music* backgroundMusic = Mix_LoadMUS("audio/theme.wav");
    if (backgroundMusic == nullptr) {
        std::cerr << "Erro ao carregar a música de fundo: " << Mix_GetError() << std::endl;
    }
    else {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    if (!isFrozen) {
        for (int i = 0; i < 4; ++i) { // 5 inimigos iniciais
            Enemy* enemy = new Enemy(graphicInterface->getSdlRenderer());
            enemy->setPosition(Vector(100 * i, 100 + 50 * i)); // Posiciona os inimigos
            enemies.push_back(enemy);
        }
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
        if(!isFrozen) {
            this->update(SecsBetweenUpdate);
        }
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
    graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(1750, 7), { 255, 255, 255, 255 }, 30);

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

void Game::showStartMenu() {
    bool menuActive = true;
    isFrozen = true;
    eventInterface->setIsRunning(false);
    int selectedOption = 0; // 0 = Iniciar, 1 = Sair, 2 = Teclas, 3 = Leaderboard

    while (menuActive) {

        SDL_Surface* tempSurface = IMG_Load("sprite/matrix.jpg");
        if (tempSurface == nullptr) {
            std::cerr << "Erro ao carregar a imagem de fundo: " << IMG_GetError() << std::endl;
        }
        else {
            backgroundTexture = SDL_CreateTextureFromSurface(graphicInterface->getSdlRenderer(), tempSurface);
            SDL_FreeSurface(tempSurface);
            SDL_Rect destRect = { 0, 0, 1920, 1080 }; // Ajuste conforme a resolução da sua tela
            SDL_RenderCopy(graphicInterface->getSdlRenderer(), backgroundTexture, NULL, &destRect);
        }

        const SDL_Color corSelecionado = { 255, 255, 0, 255 };
        const SDL_Color corDesselecionado = { 255, 255, 255, 255 };
        graphicInterface->drawText("Iniciar", Vector(900, 400), selectedOption == 0 ? corSelecionado : corDesselecionado, 30);
        graphicInterface->drawText("Sair", Vector(900, 450), selectedOption == 1 ? corSelecionado : corDesselecionado, 30);
        graphicInterface->drawText("Leaderboard", Vector(900, 500), selectedOption == 2 ? corSelecionado : corDesselecionado, 30);
        graphicInterface->drawText("Creditos", Vector(900, 550), selectedOption == 3 ? corSelecionado : corDesselecionado, 30);
        graphicInterface->drawText("Comandos", Vector(950, 600), corDesselecionado, 30);
        graphicInterface->drawText("Movimentos: Setas", Vector(900, 650), corDesselecionado, 30);
        graphicInterface->drawText("Tiro: Z", Vector(900, 700), corDesselecionado, 30);

        graphicInterface->updateRender();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                menuActive = false;
                eventInterface->setIsRunning(false);
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selectedOption = (selectedOption > 0) ? selectedOption - 1 : 3;
                    break;
                case SDLK_DOWN:
                    selectedOption = (selectedOption < 3) ? selectedOption + 1 : 0;
                    break;
                case SDLK_RETURN:
                    if (selectedOption == 0) {
                        isFrozen = false;
                        eventInterface->setIsRunning(true);
                        menuActive = false; // Começa o jogo
                    }
                    else if (selectedOption == 1) {
                        eventInterface->setIsRunning(false); // Sai do jogo
                        menuActive = false;
                    }
                    else if (selectedOption == 2) {
                        showLeaderboard(); // Exibe o leaderboard
                    }
                    else if (selectedOption == 3) {
                        showEndCredits(); // Exibe o leaderboard
                    }
                    break;
                }
            }
        }
    }
}

void Game::showLeaderboard() {
    SDL_Surface* tempSurface = IMG_Load("sprite/matrix.jpg");
    if (tempSurface == nullptr) {
        std::cerr << "Erro ao carregar a imagem de fundo: " << IMG_GetError() << std::endl;
    }
    else {
        backgroundTexture = SDL_CreateTextureFromSurface(graphicInterface->getSdlRenderer(), tempSurface);
        SDL_FreeSurface(tempSurface);
        SDL_Rect destRect = { 0, 0, 1920, 1080 }; // Ajuste conforme a resolução da sua tela
        SDL_RenderCopy(graphicInterface->getSdlRenderer(), backgroundTexture, NULL, &destRect);
    }
    std::ifstream scoreFile("scores.txt");
    std::string line;
    int yOffset = 300;

    if (scoreFile.is_open()) {
        graphicInterface->drawText("Leaderboard", Vector(850, 200), { 255, 255, 255, 255 }, 30);

        while (getline(scoreFile, line)) {
            graphicInterface->drawText(line, Vector(850, yOffset), { 255, 255, 255, 255 }, 30);
            yOffset += 30; // Distância entre linhas
        }
        scoreFile.close();
    }
    else {
        graphicInterface->drawText("Erro ao carregar leaderboard", Vector(850, 200), { 255, 0, 0, 255 }, 30);
    }

    graphicInterface->updateRender();

    // Espera o jogador pressionar uma tecla para sair do leaderboard
    SDL_Event event;
    bool leaderboardActive = true;
    while (leaderboardActive) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                leaderboardActive = false; // Sai do leaderboard
            }
        }
    }
}

void Game::showGameOverScreen() {
    graphicInterface->clearRender({ 0, 0, 0, 255 });
    graphicInterface->drawText("Game Over", Vector(880, 480), { 255, 255, 255, 255 }, 30);
    graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(880, 520), { 255, 255, 255, 255 }, 30);
    graphicInterface->drawText("Digite 3 letras e pressione Enter:", Vector(880, 560), { 255, 255, 255, 255 }, 30);
    graphicInterface->updateRender();

    std::string initials = "";
    SDL_Event event;
    bool enterPressed = false;

    while (!enterPressed) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z && initials.size() < 3) {
                    initials += static_cast<char>(event.key.keysym.sym);
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && !initials.empty()) {
                    initials.pop_back();  // Remove a última letra
                }
                else if (event.key.keysym.sym == SDLK_RETURN && initials.size() == 3) {
                    enterPressed = true;  // Pressionou Enter com 3 letras
                }

                // Atualiza a tela com as letras digitadas
                graphicInterface->clearRender({ 0, 0, 0, 255 });
                graphicInterface->drawText("Game Over", Vector(880, 480), { 255, 255, 255, 255 }, 30);
                graphicInterface->drawText("Score: " + std::to_string(player->getScore()), Vector(880, 520), { 255, 255, 255, 255 }, 30);
                graphicInterface->drawText("Digite 3 letras e pressione Enter:", Vector(880, 560), { 255, 255, 255, 255 }, 30);
                graphicInterface->drawText("Iniciais: " + initials, Vector(880, 600), { 255, 255, 255, 255 }, 30);
                graphicInterface->updateRender();
            }
        }
    }

    // Salva o nome e a pontuação no arquivo
    std::ofstream scoreFile("scores.txt", std::ios::app);
    if (scoreFile.is_open()) {
        scoreFile << initials << " : " << player->getScore() << "\n";
        scoreFile.close();
    }
    else {
        std::cerr << "Erro ao salvar pontuação" << std::endl;
    }

    // Retorna ao menu inicial após salvar
    showStartMenu();
}

void Game::showEndCredits() {
    SDL_Surface* tempSurface = IMG_Load("sprite/matrix.jpg");
    if (tempSurface == nullptr) {
        std::cerr << "Erro ao carregar a imagem de fundo: " << IMG_GetError() << std::endl;
    }
    else {
        backgroundTexture = SDL_CreateTextureFromSurface(graphicInterface->getSdlRenderer(), tempSurface);
        SDL_FreeSurface(tempSurface);
        SDL_Rect destRect = { 0, 0, 1920, 1080 }; // Ajuste conforme a resolução da sua tela
        SDL_RenderCopy(graphicInterface->getSdlRenderer(), backgroundTexture, NULL, &destRect);
    }
    graphicInterface->drawText("Creditos finais", Vector(700, 100), { 255, 255, 255, 255 }, 50);
    graphicInterface->drawText("Desenvolvido por: Carlos Eduardo e Leonardo Sarto", Vector(500, 240), { 255, 255, 255, 255 }, 30);
    graphicInterface->drawText("Disciplinas ministradas: Topicos em Computacao e Projeto de Software Avancado", Vector(500, 300), { 255, 255, 255, 255 }, 30);
    graphicInterface->drawText("Orientado pelos professores: Eduardo Henrique e Helio Kamakawa", Vector(500, 350), { 255, 255, 255, 255 }, 30);
    graphicInterface->drawText("Pressione qualquer tecla para voltar ao Menu inicial", Vector(500, 400), { 255, 255, 255, 255 }, 30);
    graphicInterface->updateRender();

    SDL_Event event;
    bool showEndCredits = true;

    while (showEndCredits) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                showEndCredits = false;
            }
        }
    }
}
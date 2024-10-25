#define SDL_MAIN_HANDLED
#include <cassert>
#include <iostream>
#include "../player.hpp"
#include "../graphic-implement-sdl.hpp"
#include "../status-bar.hpp"
#include "../sprite.hpp"
#include "../bullet.hpp"
#include "../enemy.hpp"

int main() {
    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Falha ao inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Cria uma janela SDL
    SDL_Window* window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Falha ao criar janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Cria um renderer SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Falha ao criar renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Cria um Player
    Player player(renderer);

    // Verifica a inicialização dos atributos
    assert(player.getLife() == 3);
    assert(player.isDead() == false);
    assert(player.getIsBlinking() == false);

    std::cout << "Player criado com sucesso e atributos inicializados corretamente." << std::endl;

    // Testa a funcionalidade de tomar dano
    player.takeDamage(1);
    assert(player.getLife() == 2);
    assert(player.isDead() == false);

    // Simula o tempo passando para garantir que o jogador não esteja piscando (invencível)
    float deltaTime = 0.1f;
    for (int i = 0; i < 10; ++i) {
        player.update(deltaTime);
    }

    player.takeDamage(2);
    assert(player.getLife() == 0);
    assert(player.isDead() == true);

    std::cout << "Funcionalidade de tomar dano testada e funcionando com sucesso." << std::endl;

    // Limpa recursos SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
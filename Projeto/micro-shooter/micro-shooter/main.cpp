#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"

Game* game = nullptr;
Player* player = nullptr;
Enemy* enemy = nullptr;

int main(int argc, char* argv[]) {
	game = new Game("Microshooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false);
	player = new Player();
	enemy = new Enemy();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	while (game->running())
	{
		game->render();
		game->handleEvents();
		player->draw(game->renderer);
		enemy->draw(game->renderer);
		SDL_RenderPresent(game->renderer);

		if (keys[SDL_SCANCODE_RIGHT])
		{
			player->moveRight();
		}
		if (keys[SDL_SCANCODE_LEFT])
		{
			player->moveLeft();
		}
		if (keys[SDL_SCANCODE_DOWN])
		{
			player->moveDown();
		}
		if (keys[SDL_SCANCODE_UP])
		{
			player->moveUp();
		}

		SDL_Delay(10);
	}

	game->clean();


	return 0;
}

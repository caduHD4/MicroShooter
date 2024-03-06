#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"

Game* game = nullptr;
Player* player = nullptr;
Enemy* enemy = nullptr;

int main(int argc, char* argv[]) {
	game = new Game();
	player = new Player();
	enemy = new Enemy();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	while (game->getIsRunning())
	{
		game->render();
		game->handleEvents();
		player->draw(game->getRenderer());
		enemy->draw(game->getRenderer());
		SDL_RenderPresent(game->getRenderer());

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
		if (keys[SDL_SCANCODE_ESCAPE]) {
			game->setIsRunning(false);
		}
		if (SDL_HasIntersection(player->getRect(), enemy->getRect()) == 0)
		{
			player->setSpeed(Vector(6, 1));
			SDL_Log("Calma la paizao, ele nem encostou nela");
		} else {
			Vector finalPosition = player->getPosition();
			float dt = 2.0;
			if (enemy->getPosition().x <= player->getPosition().x) {
				finalPosition += player->getSpeed() * dt;
			}
			else
			{
				finalPosition -= player->getSpeed() * dt;
			}
			player->setPosition(finalPosition);
			player->setSpeed(Vector(0, 1));
			SDL_Log("Nao tenha calma paizao, ele encostou");
		}

		SDL_Delay(10);
	}

	game->clean();

	return 0;
}

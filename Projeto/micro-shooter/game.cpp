#include "Game.hpp"
#include "graphic-interface.hpp"
#include "graphic-implement-sdl.hpp"

Game::Game()
{
	graphicInterface = new GraphicImplementSdl();
	setIsRunning(true);
	FPS = 60.0;
	frameDelay = 1000.0 / FPS;
	frameTime = 0;

	while (getIsRunning())
	{
		frameStart = SDL_GetTicks();
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		render();
		handleEvents();
		player.draw(getRenderer());
		enemy.draw(getRenderer());

		if (keys[SDL_SCANCODE_RIGHT])
		{
			player.moveRight(frameTime);
		}
		if (keys[SDL_SCANCODE_LEFT])
		{
			player.moveLeft(frameTime);
		}
		if (keys[SDL_SCANCODE_DOWN])
		{
			player.moveDown(frameTime);
		}
		if (keys[SDL_SCANCODE_UP])
		{
			player.moveUp(frameTime);
		}
		if (keys[SDL_SCANCODE_ESCAPE]) {
			setIsRunning(false);
		}
		if (keys[SDL_SCANCODE_Z]) {
			SDL_Log("Atirou!");
			//bullet.draw(getRenderer());
		}
		/*if (SDL_HasIntersection(this->player.getRect(), this->enemy.getRect()) == 0)
		{
			player.setSpeed(Vector(300, 300));
		} else {
			Vector finalPosition = player.getPosition();
			float dt = 2.0;
			if (enemy.getPosition().x <= player.getPosition().x) {
				finalPosition += player.getSpeed() * dt;
			}
			else
			{
				finalPosition -= player.getSpeed() * dt;
			}
			player.setPosition(finalPosition);
			player.setSpeed(Vector(0, 1));
		}*/
		SDL_RenderPresent(getRenderer());

		frameTime = static_cast<float>(SDL_GetTicks() - frameStart) / 1000.0f;
	}

	clean();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

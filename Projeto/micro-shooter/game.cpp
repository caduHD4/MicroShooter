#include "Game.hpp"
#include "graphic-implement-sdl.cpp"
#include "event-implement-sdl.cpp"

Game::Game()
{
	const color backgroundColor = {0, 0, 255, 255};
	graphicInterface = new GraphicImplementSdl();
	eventInterface = new EventImplementSdl();
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
		graphicInterface->clearRender(backgroundColor);

		eventInterface->setPlayer(player);
		eventInterface->handleEvents();

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
		graphicInterface->updateRender();
		frameTime = static_cast<float>(SDL_GetTicks() - frameStart) / 1000.0f;
	}

	graphicInterface->cleanWindow();
}

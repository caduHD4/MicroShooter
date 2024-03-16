#include "Game.hpp"
#include "graphic-implement-sdl.cpp"
#include "input-implement-sdl.cpp"

Game::Game()
{
	const color backgroundColor = {0, 0, 255, 255};
	graphicInterface = new GraphicImplementSdl();
	inputInterface = new InputImplementSdl();
	setIsRunning(true);
	FPS = 60.0;
	frameDelay = 1000.0 / FPS;
	frameTime = 0;
	inputInterface->getInputs();

	while (getIsRunning())
	{
		frameStart = SDL_GetTicks();
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		graphicInterface->clearRender(backgroundColor);

		inputInterface->handleInputEvents();

		if (inputInterface->keyPressed == 1)
		{
			player.moveLeft(frameTime);
		}

		if (keys[SDL_SCANCODE_RIGHT])
		{
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
		graphicInterface->updateRender();
		frameTime = static_cast<float>(SDL_GetTicks() - frameStart) / 1000.0f;
	}

	graphicInterface->cleanWindow();
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

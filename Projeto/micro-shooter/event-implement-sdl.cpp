#include "event-implement-sdl.hpp"

void EventImplementSdl::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				this->setIsRunning(false);
				break;
			}

			case SDL_KEYDOWN: {
				this->handleInputEvents(event);
				break;
			}
		}
	}
}


void EventImplementSdl::handleInputEvents(SDL_Event& event)
{
	switch (event.key.keysym.sym) {
		case SDLK_LEFT: {
			this->getPlayer().moveLeft(this->getFrameTime());
			break;
		}

		case SDLK_RIGHT: {
			this->getPlayer().moveRight(this->getFrameTime());
			break;
		}

		case SDLK_UP: {
			this->getPlayer().moveUp(this->getFrameTime());
			break;
		}

		case SDLK_DOWN: {
			this->getPlayer().moveDown(this->getFrameTime());
			break;
		}

		case SDLK_ESCAPE: {
			break;
		}

		case SDLK_z: {
			break;
		}
	}
}
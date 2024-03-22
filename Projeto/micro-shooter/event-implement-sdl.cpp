#include "event-implement-sdl.hpp"

EventImplementSdl::EventImplementSdl()
{

}

void EventImplementSdl::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
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
			getPlayer()->moveLeft();
			break;
		

		case SDLK_RIGHT: {
			break;
		}

		case SDLK_UP: {
			break;
		}

		case SDLK_DOWN: {
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
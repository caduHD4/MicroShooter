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
    switch (event.type) {
    case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT: {
            printf("Tecla LEFT pressionada\n");
            this->getPlayer().move(-1.0f, 0.0f, this->getFrameTime());
            break;
        }

        case SDLK_RIGHT: {
            printf("Tecla RIGHT pressionada\n");
            this->getPlayer().move(1.0f, 0.0f, this->getFrameTime());
            break;
        }

        case SDLK_UP: {
            printf("Tecla UP pressionada\n");
            this->getPlayer().move(0.0f, -1.0f, this->getFrameTime());
            break;
        }

        case SDLK_DOWN: {
            printf("Tecla DOWN pressionada\n");
            this->getPlayer().move(0.0f, 1.0f, this->getFrameTime());
            break;
        }

        case SDLK_ESCAPE: {
            printf("Tecla ESC pressionada\n");
            // Lógica para lidar com ESC, se necessário
            break;
        }

        case SDLK_z: {
            printf("Tecla Z pressionada\n");
            // Lógica para lidar com Z, se necessário
            break;
        }

        default:
            break;
        }
        break;
    }
    }
}

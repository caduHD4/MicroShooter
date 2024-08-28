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
            printf("Tecla LEFT\n");
            getPlayer()->moveLeft(this->getFrameTime());
            break;
        }

        case SDLK_RIGHT:{
            printf("Tecla RIGHT\n");
            getPlayer()->moveRight(this->getFrameTime());
            break;
        }

        case SDLK_UP: {
            printf("Tecla UP\n");
            getPlayer()->moveUp(this->getFrameTime());
            break;
        }

        case SDLK_DOWN: {
            printf("Tecla DOWN\n");
            getPlayer()->moveDown(this->getFrameTime());
            break;
        }

        case SDLK_ESCAPE: {
            printf("Tecla ESC pressionada\n");
            // Lógica para lidar com ESC, se necessário
            break;
        }

        case SDLK_z: {
            printf("Tecla Z pressionada\n");
            // Tiro do jogador
            break;
        }

        case SDLK_x: {
            printf("Tecla X pressionada\n");
            // Tiro do jogador
            break;
        }

        default:
            break;
        }
        break;
    }
    }
}


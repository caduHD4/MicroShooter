#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <list>
#include "player.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "graphic-interface.hpp"

class Game {
private:
	bool isRunning;
	std::list<Object*> objectList;
	const Uint8* keys;
	Player player;
	Enemy enemy;
	Bullet bullet;
	float FPS;
	float frameDelay;
	Uint32 frameStart;
	float frameTime;
	GraphicInterface* graphicInterface;

public:
	Game();
	void handleEvents();
	void render();
	void clean();

	bool getIsRunning() {
		return this->isRunning;
	}

	void setIsRunning(bool isRunning) {
		this->isRunning = isRunning;
	}

	SDL_Window* getWindow() {
		return this->window;
	}

	void setWindow(SDL_Window* window) {
		this->window = window;
	}

	SDL_Renderer* getRenderer() {
		return this->renderer;
	}

	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
};
#endif
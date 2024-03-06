#define game_hpp
#include "SDL.h"
#include <stdio.h>
#include<iostream>

class Game {
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

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
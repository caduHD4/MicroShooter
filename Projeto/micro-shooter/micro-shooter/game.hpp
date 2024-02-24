#define game_hpp
#include "SDL.h"
#include <stdio.h>
#include<iostream>

class Game {
public:
	bool isRunning;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool running() { return isRunning; };
	void handleEvents();
	void update();
	void render();
	void clean();
};
#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <list>
#include "player.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "graphic-interface.hpp"
#include "input-interface.hpp"

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
	InputInterface* inputInterface;

public:
	Game();
	void handleEvents();
	void render();

	bool getIsRunning() {
		return this->isRunning;
	}

	void setIsRunning(bool isRunning) {
		this->isRunning = isRunning;
	}
};
#endif
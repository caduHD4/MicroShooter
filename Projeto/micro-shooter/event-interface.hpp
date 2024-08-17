#ifndef event_interface_hpp
#define event_interface_hpp

#include <stdio.h>
#include "player.hpp"

class EventInterface
{
private:
	Player player; // Player duplicando, declarar como ponteiro
	bool isRunning;

public:
	virtual void handleEvents() = 0;
	Player& getPlayer()
	{
		return this->player;
	}
	void setPlayer(Player& player) // ele copiando, n referenciando!
	{
		this->player = player;
	}

	bool getIsRunning()
	{
		return this->isRunning;
	}

	void setIsRunning(bool isRunning)
	{
		this->isRunning = isRunning;
	}
};
#endif
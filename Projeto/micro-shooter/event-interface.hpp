#ifndef event_interface_hpp
#define event_interface_hpp

#include <stdio.h>
#include "player.hpp"

class EventInterface
{
private:
	Player player;
	bool isRunning;

public:
	virtual void handleEvents() = 0;
	Player& getPlayer()
	{
		return this->player;
	}
	void setPlayer(Player& player)
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
#ifndef event_interface_hpp
#define event_interface_hpp

#include <stdio.h>
#include "player.hpp"

class EventInterface
{
private:
	Player player;

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
};
#endif
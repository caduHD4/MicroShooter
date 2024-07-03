#ifndef event_implement_sdl_hpp
#define event_implement_sdl_hpp

#include <stdio.h>
#include "SDL.h"
#include "event-interface.hpp"

class EventImplementSdl : public EventInterface
{
private:
	float frameTime;
	bool isRunning;

public:
	void handleEvents() override final;
	void handleInputEvents(SDL_Event& event);

	float getFrameTime()
	{
		return this->frameTime;
	}

	void setFrameTime(float frameTime)
	{
		this->frameTime = frameTime;
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
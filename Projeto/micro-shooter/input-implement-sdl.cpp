#include "input-implement-sdl.hpp"

InputImplementSdl::InputImplementSdl()
{

}

void InputImplementSdl::getInputs()
{
	setKeys(SDL_GetKeyboardState(NULL));
}

void InputImplementSdl::handleInputEvents()
{
	if (getKeys()[SDL_SCANCODE_RIGHT])
	{
		keyPressed = 0;
	}
	if (getKeys()[SDL_SCANCODE_LEFT])
	{
		keyPressed = 1;
	}
	if (getKeys()[SDL_SCANCODE_DOWN])
	{
		keyPressed = 2;
	}

	if (getKeys()[SDL_SCANCODE_UP])
	{
		keyPressed = 3;
	}
	if (getKeys()[SDL_SCANCODE_ESCAPE])
	{
		keyPressed = 4;
	}
}
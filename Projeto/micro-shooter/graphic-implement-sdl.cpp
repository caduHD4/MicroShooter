#include "graphic-implement-sdl.hpp"

GraphicImplementSdl::GraphicImplementSdl()
{
	showWindow();
	setKeys(SDL_GetKeyboardState(NULL));
}

void GraphicImplementSdl::showWindow()
{
	setWindow(SDL_CreateWindow("Microshooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false));
}

void GraphicImplementSdl::drawRect(const rect& objectRect)
{
	SDL_Rect rect;
	rect.w = objectRect.width;
	rect.h = objectRect.height;
	rect.x = objectRect.position.x;
	rect.y = objectRect.position.y;
	SDL_SetRenderDrawColor(getSdlRenderer(), 32, 33, 36, 255);
	SDL_RenderFillRect(getSdlRenderer(), &rect);
}

void GraphicImplementSdl::createRenderer()
{
	setWindow(SDL_CreateWindow("Microshooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false));
}
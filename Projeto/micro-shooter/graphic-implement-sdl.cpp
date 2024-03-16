#include "graphic-implement-sdl.hpp"

GraphicImplementSdl::GraphicImplementSdl()
{
	const windows window = {"Microshooter", Vector(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), 1000, 1000, false};
	showWindow(window);
	createRenderer();
}

void GraphicImplementSdl::showWindow(const windows& createWindow)
{
	setWindow(SDL_CreateWindow(createWindow.title, createWindow.position.x, createWindow.position.y, createWindow.width, createWindow.height, createWindow.fullscreen));
}

void GraphicImplementSdl::drawRect(const rect& objectRect, const color& colorRect)
{
	const SDL_Rect rect = { objectRect.position.x, objectRect.position.y, objectRect.width, objectRect.height };
	SDL_SetRenderDrawColor(getSdlRenderer(), colorRect.r, colorRect.g, colorRect.b, colorRect.a);
	SDL_RenderFillRect(getSdlRenderer(), &rect);
}

void GraphicImplementSdl::createRenderer()
{
	setSdlRenderer(SDL_CreateRenderer(getWindow(), -1, false));
}

void GraphicImplementSdl::cleanWindow()
{
	SDL_DestroyWindow(getWindow());
	SDL_DestroyRenderer(getSdlRenderer());
	SDL_Quit();
}

void GraphicImplementSdl::clearRender(const color& colorRender)
{
	SDL_SetRenderDrawColor(getSdlRenderer(), colorRender.r, colorRender.g, colorRender.b, colorRender.a);
	SDL_RenderClear(getSdlRenderer());
}

void GraphicImplementSdl::updateRender()
{
	SDL_RenderPresent(getSdlRenderer());
}
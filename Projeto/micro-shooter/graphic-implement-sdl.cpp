#include "graphic-implement-sdl.hpp"

GraphicImplementSdl::GraphicImplementSdl()
{
	const windows window = { "Microshooter", Vector(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), 1000, 1000, false };
	showWindow(window);
	createRenderer();
}

void GraphicImplementSdl::showWindow(const windows& createWindow)
{
	setWindow(SDL_CreateWindow(createWindow.title, createWindow.position.x, createWindow.position.y, createWindow.width, createWindow.height, createWindow.fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
}

void GraphicImplementSdl::drawRect(const Rect& objectRect, const Color& colorRect)
{
	SDL_Rect rect = { static_cast<int>(objectRect.position.x), static_cast<int>(objectRect.position.y), static_cast<int>(objectRect.width), static_cast<int>(objectRect.height) };
	SDL_SetRenderDrawColor(getSdlRenderer(), colorRect.r, colorRect.g, colorRect.b, static_cast<Uint8>(colorRect.a * 255));
	SDL_RenderFillRect(getSdlRenderer(), &rect);
}


void GraphicImplementSdl::createRenderer()
{
	setSdlRenderer(SDL_CreateRenderer(getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
}


void GraphicImplementSdl::cleanWindow()
{
	SDL_DestroyWindow(getWindow());
	SDL_DestroyRenderer(getSdlRenderer());
	SDL_Quit();
}

void GraphicImplementSdl::clearRender(const Color& colorRender)
{
	SDL_SetRenderDrawColor(getSdlRenderer(), colorRender.r, colorRender.g, colorRender.b, colorRender.a);
	SDL_RenderClear(getSdlRenderer());
}

void GraphicImplementSdl::updateRender()
{
	SDL_RenderPresent(getSdlRenderer());
}

#include "graphic-implement-sdl.hpp"
#include <SDL_ttf.h>

GraphicImplementSdl::GraphicImplementSdl()
{
	const windows window = { "Microshooter", Vector(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), 1080, 1920, false};
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

void GraphicImplementSdl::drawText(const std::string& text, const Vector& position, const SDL_Color& color) {
	// Supondo que você tenha uma fonte carregada
	TTF_Font* font = TTF_OpenFont("fonte/gameover.ttf", 30);
	if (!font) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

	SDL_Rect dstRect = { static_cast<int>(position.x), static_cast<int>(position.y), surface->w, surface->h };
	SDL_RenderCopy(sdlRenderer, texture, NULL, &dstRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}
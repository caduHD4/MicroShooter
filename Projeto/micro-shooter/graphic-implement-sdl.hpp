#ifndef graphic_implement_sdl_hpp
#define graphic_implement_sdl_hpp

#include <stdio.h>
#include "SDL.h"
#include "graphic-interface.hpp"

class GraphicImplementSdl : public GraphicInterface
{
	private:
		const Uint8* keys;
		SDL_Window* window;
		SDL_Renderer* sdlRenderer;

	public:
		GraphicImplementSdl();
		void showWindow() override final;
		void drawRect(const rect&) override final;
		void createRenderer() override final;

		SDL_Window* getWindow()
		{
			return this->window;
		}

		void setWindow(SDL_Window* window)
		{
			this->window = window;
		}

		const Uint8* getKeys()
		{
			return this->keys;
		}

		void setKeys(const Uint8* keys)
		{
			this->keys = keys;
		}

		SDL_Renderer* getSdlRenderer()
		{
			return this->sdlRenderer;
		}

		void setSdlRenderer(SDL_Renderer* sdlRenderer)
		{
			this->sdlRenderer = sdlRenderer;
		}
};
#endif
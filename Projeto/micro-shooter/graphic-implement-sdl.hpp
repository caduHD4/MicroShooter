#ifndef graphic_implement_sdl_hpp
#define graphic_implement_sdl_hpp

#include <stdio.h>
#include "SDL.h"
#include "graphic-interface.hpp"

class GraphicImplementSdl : public GraphicInterface
{
	private:
		SDL_Window* window;
		SDL_Renderer* sdlRenderer;

	public:
		GraphicImplementSdl();
		void showWindow(const windows&) override final;
		void drawRect(const Rect&, const Color&) override final;
		void createRenderer() override final;
		void cleanWindow() override final;
		void clearRender(const Color&) override final;
		void updateRender() override final;
		void drawText(const std::string& text, const Vector& position, const SDL_Color& color);

		SDL_Window* getWindow()
		{
			return this->window;
		}

		void setWindow(SDL_Window* window)
		{
			this->window = window;
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
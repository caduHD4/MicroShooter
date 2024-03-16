#ifndef input_implement_sdl_hpp
#define input_implement_sdl_hpp

#include <stdio.h>
#include "SDL.h"
#include "input-interface.hpp"

class InputImplementSdl : public InputInterface
{
private:
	const Uint8* keys;

public:
	InputImplementSdl();

	void getInputs() override final;
	void handleInputEvents() override final;

	const Uint8* getKeys() {
		return this->keys;
	}

	void setKeys(const Uint8* keys) {
		this->keys = keys;
	}
};
#endif
#ifndef input_interface_hpp
#define input_interface_hpp

#include <stdio.h>

class InputInterface
{
public:
	int keyPressed;
	virtual void getInputs() = 0;
	virtual void handleInputEvents() = 0;
};
#endif
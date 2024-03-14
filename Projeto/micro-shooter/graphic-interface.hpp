#ifndef graphic_interface_hpp
#define graphic_interface_hpp

#include <stdio.h>
#include "math-vector.h"
#include <stdint.h>

using Vector = Mylib::Math::Vector<float, 2>;
struct rect {
	Vector position;
	float width;
	float height;
};

struct color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	float a;
};

class GraphicInterface
{
	public:
		virtual void drawRect(const rect&) = 0;
		virtual void showWindow() = 0;
		virtual void createRenderer() = 0;
};
#endif
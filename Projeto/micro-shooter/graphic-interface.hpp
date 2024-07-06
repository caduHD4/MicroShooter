#ifndef graphic_interface_hpp
#define graphic_interface_hpp

#include <stdio.h>
#include "math-vector.h"
#include <stdint.h>

using Vector = Mylib::Math::Vector<float, 2>;

struct windows {
	const char* title;
	Vector position;
	float height;
	float width;
	bool fullscreen;
};

struct Rect {
	Vector position;
	float width;
	float height;
};

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	float a;
};

class GraphicInterface
{
	public:
		virtual void drawRect(const Rect&, const Color&) = 0;
		virtual void showWindow(const windows&) = 0;
		virtual void createRenderer() = 0;
		virtual void cleanWindow() = 0;
		virtual void clearRender(const Color&) = 0;
		virtual void updateRender() = 0;
};
#endif
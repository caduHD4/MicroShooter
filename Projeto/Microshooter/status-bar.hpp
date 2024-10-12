#ifndef status_bar_hpp
#define status_bar_hpp
#include "graphic-implement-sdl.hpp"

struct StatusBarInitialization {
	float width;
	Color backgroundColor;
	Color foregroundColor;
	Vector position;
};

class StatusBar {

private:
	float width;
	Color backgroundColor;
	Color foregroundColor;
	Vector position;
	float height = 8.0f;
	float percentage = 100.0f;

public:
	StatusBar();
	StatusBar(const StatusBarInitialization& statusBarInitialization);
	void drawStatusBar(GraphicImplementSdl* graphicInterface);
		
	float getHeight() {
		return height;
	}

	void setHeight(float Height) {
		this->height = Height;
	}

	float getWidth() {
		return width;
	}

	void setWidth(float Width) {
		this->width = Width;
	}

	Color getBackgroundColor() {
		return backgroundColor;
	}

	void setBackgroundColor(Color BackgroundColor) {
		this->backgroundColor = BackgroundColor;
	}

	Color getForegroundColor() {
		return this->foregroundColor;
	}

	void setForegroundColor(Color ForegroundColor) {
		this->foregroundColor = ForegroundColor;
	}

	Vector getPosition() {
		return position;
	}

	void setPosition(Vector Position) {
		this->position = Position;
	}
	
	float getPercentage() {
		return percentage;
	}

	void setPercentage(float percentage) {
		this->percentage = percentage;
	}
};
#endif
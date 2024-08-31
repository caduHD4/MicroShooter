#include "status-bar.hpp"

StatusBar::StatusBar() {
}

StatusBar::StatusBar(const StatusBarInitialization& statusBarInitialization) {
    backgroundColor = statusBarInitialization.backgroundColor;
    foregroundColor = statusBarInitialization.foregroundColor;
    width = statusBarInitialization.width;
    position = statusBarInitialization.position;
}

void StatusBar::drawStatusBar(GraphicImplementSdl* graphicInterface) {
    float currentWidth = width * percentage;

    if (currentWidth > width) {
        currentWidth = width;
    }

    Rect background = { position, width, height};
    Rect foreground = { position, currentWidth, height };

    graphicInterface->drawRect(background, backgroundColor);
    graphicInterface->drawRect(foreground, foregroundColor);
}
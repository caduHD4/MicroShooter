#include "status-bar.hpp"

StatusBar::StatusBar() {

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
#include "display.h"

namespace gui {

void Display::rawButtonPressed(uint8_t button)
{
    buttonPressed(espgui::Button(button));
}

void Display::rawButtonReleased(uint8_t button)
{
    buttonReleased(espgui::Button(button));
}

} // namespace gui

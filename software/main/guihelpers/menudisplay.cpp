#include "menudisplay.h"

namespace gui {

void MenuDisplay::rawButtonPressed(uint8_t button)
{
    buttonPressed(espgui::Button(button));
}

void MenuDisplay::rawButtonReleased(uint8_t button)
{
    buttonReleased(espgui::Button(button));
}

} // namespace gui

#include "displaywithtitle.h"

namespace gui {

void DisplayWithTitle::rawButtonPressed(uint8_t button)
{
    buttonPressed(espgui::Button(button));
}

void DisplayWithTitle::rawButtonReleased(uint8_t button)
{
    buttonReleased(espgui::Button(button));
}

} // namespace gui

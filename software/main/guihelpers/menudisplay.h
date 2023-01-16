#pragma once

// 3rdparty lib includes
#include <menudisplay.h>

namespace gui {

class MenuDisplay : public espgui::MenuDisplay
{
    using Base = espgui::MenuDisplay;
public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;
};

} // namespace gui

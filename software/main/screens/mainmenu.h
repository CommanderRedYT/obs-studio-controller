#pragma once

// local includes
#include "guihelpers/menudisplay.h"

namespace gui {

class MainMenu : public gui::MenuDisplay
{
    using Base = gui::MenuDisplay;
public:
    MainMenu();

    std::string title() const override;

    void back() override;
};

} // namespace gui

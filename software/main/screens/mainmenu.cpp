#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <fmt/core.h>
#include <menuitem.h>

// local includes
#include "guihelpers/menudisplay.h"

namespace gui {

namespace {
constexpr char TEXT_FOO[] = "Foo";
}

MainMenu::MainMenu()
{
    using namespace espgui;

    for (uint8_t i = 0; i < 20; i++)
    {
        auto &menuItem = constructMenuItem<makeComponent<MenuItem, ChangeableText, DummyAction>>();
        menuItem.setTitle(fmt::format("{}{}", TEXT_FOO, i));
    }
}

std::string MainMenu::title() const
{
    return "Main Menu";
}

void MainMenu::back() {}

}

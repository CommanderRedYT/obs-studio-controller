#include "screens.h"

// 3rdparty lib includes
#include <TFT_eSPI.h>
#include <delayedconstruction.h>
#include <espchrono.h>
#include <fontrenderer.h>
#include <screenmanager.h>
#include <tftcolors.h>
#include <tftinterface.h>
#include <widgets/label.h>

// local includes
#include "icons/bootlogo.h"
#include "settings.h"

using namespace std::chrono_literals;

namespace display {
namespace {
constexpr const char * const TAG = "DISPLAY";

TFT_eSPI tft;

cpputils::DelayedConstruction<espgui::Label> bootLabel;
} // namespace

espchrono::millis_clock::time_point lastDisplayUpdate;
espchrono::millis_clock::time_point lastDisplayRedraw;

void init()
{
    tft.init();
    tft.setRotation(configs.displayRotated.value() ? 1 : 3);
    tft.fillScreen(espgui::TFT_BLACK);
    tft.pushImage((tft.width() / 2) - (icons::bootlogo.WIDTH / 2), (tft.height() / 2) - (icons::bootlogo.HEIGHT / 2), icons::bootlogo.WIDTH, icons::bootlogo.HEIGHT, icons::bootlogo.buffer);
    bootLabel.construct(220, tft.height() - 50);
    bootLabel->start(tft);
}

void update()
{
    if (tft.getRotation() != (configs.displayRotated.value() ? 1 : 3))
    {
        tft.setRotation(configs.displayRotated.value() ? 1 : 3);

        if (espgui::currentDisplay)
            espgui::currentDisplay->initScreen(tft);
    }

    if (espchrono::ago(lastDisplayUpdate) >= 1000ms / 50)
    {
        lastDisplayUpdate = espchrono::millis_clock::now();

        if (espgui::currentDisplay)
            espgui::currentDisplay->update();

        if (espgui::changeScreenCallback)
        {
            espgui::changeScreenCallback(tft);
            espgui::changeScreenCallback = {};
        }
    }

    if (espchrono::ago(lastDisplayRedraw) >= 1000ms / 60)
    {
        lastDisplayRedraw = espchrono::millis_clock::now();

        if (espgui::currentDisplay)
            espgui::currentDisplay->redraw(tft);
    }
}

void setBootMsg(std::string_view msg)
{
    bootLabel->redraw(tft, msg, espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
}
} // namespace display

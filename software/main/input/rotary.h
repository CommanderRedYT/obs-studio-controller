#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "pins.h"

namespace input {
template<pin_t CLK, pin_t DATA>
class Rotary {
public:
    static constexpr auto CLK_PIN = CLK;
    static constexpr auto DATA_PIN = DATA;

    void begin();

    void updateRotate();
private:
    espchrono::millis_clock::time_point m_lastMillis;

    bool m_lastClk;
};
} // namespace input

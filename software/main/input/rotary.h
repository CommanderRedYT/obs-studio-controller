#pragma once

// system includes
#include <array>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "pins.h"

namespace input {
class Rotary {
public:
    Rotary(pin_t pin_clk, pin_t pin_data);

    void begin();
    void loop();
private:
    pin_t m_pin_clk;
    pin_t m_pin_data;

    int m_encoder_pos{0};
    bool m_rotating{false};

    bool m_a_set{false};
    bool m_b_set{false};

    void encoderA();
    void encoderB();
};

extern std::array<Rotary, 4> rotary_encoders;

void initRotary();
void updateRotary();
} // namespace input

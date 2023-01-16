#pragma once

// system includes
#include <cstdint>

using pin_t = uint8_t;

constexpr const pin_t SENSOR_VP = 36;
constexpr const pin_t SENSOR_VN = 39;

namespace pins {
// Buttons
#ifdef BOARD_REVISION_V1
constexpr const pin_t BUTTONS_IN_1 = 4;
constexpr const pin_t BUTTONS_IN_2 = 18;
constexpr const pin_t BUTTONS_IN_3 = 16;
constexpr const pin_t BUTTONS_IN_4 = 17;
constexpr const pin_t BUTTONS_OUT_1 = 19;
#endif

// Rotary
#ifdef BOARD_REVISION_V1
constexpr const pin_t ROTARY_1_DATA = 27;
constexpr const pin_t ROTARY_1_CLK = 26;
constexpr const pin_t ROTARY_2_DATA = 33;
constexpr const pin_t ROTARY_2_CLK = 32;
constexpr const pin_t ROTARY_3_DATA = 35;
constexpr const pin_t ROTARY_3_CLK = 34;
constexpr const pin_t ROTARY_4_DATA = 39;
constexpr const pin_t ROTARY_4_CLK = 36;
#endif

// LEDs
#ifdef BOARD_REVISION_V1
constexpr const pin_t LED_1 = 21;
constexpr const pin_t LED_2 = 22;
constexpr const pin_t LED_3 = 23;
constexpr const pin_t LED_4 = 25;
#endif

// WS2812
#ifdef BOARD_REVISION_V1
constexpr const pin_t WS2812_DATA = 5;
#endif

// Display
#ifdef BOARD_REVISION_V1
constexpr const pin_t DISPLAY_BACKLIGHT = 2;
#endif
} // namespace pins

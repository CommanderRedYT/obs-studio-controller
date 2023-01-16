#include "rotary.h"

// esp-idf includes
#include <driver/gpio.h>
#include <esp32-hal-gpio.h>
#include <esp_log.h>

// 3rdparty lib includes
#include <screenmanager.h>
#include <tickchrono.h>
#include <menudisplay.h>

// local includes
#include "utils.h"

namespace input {
using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "ROTARY";
} // namespace

Rotary::Rotary(pin_t pin_clk, pin_t pin_data) :
    m_pin_clk{pin_clk},
    m_pin_data{pin_data}
{}

void Rotary::encoderA()
{
    if (m_rotating)
    {
        espcpputils::delay(1ms); // debounce
    }

    if (digitalRead(m_pin_data) != m_a_set)
    {
        m_a_set = !m_a_set;
        if (m_a_set && !m_b_set)
            m_encoder_pos += 1;
        m_rotating = false;
    }
}

void Rotary::encoderB()
{
    if (m_rotating)
    {
        espcpputils::delay(1ms); // debounce
    }

    if (digitalRead(m_pin_clk) != m_b_set)
    {
        m_b_set = !m_b_set;
        if (m_b_set && !m_a_set)
            m_encoder_pos -= 1;
        m_rotating = false;
    }
}

void Rotary::begin()
{
    pinMode(m_pin_clk, INPUT);
    pinMode(m_pin_data, INPUT);

    attachInterrupt(m_pin_clk, [](void* args) { static_cast<Rotary*>(args)->encoderA(); }, this, GPIO_INTR_ANYEDGE);
    attachInterrupt(m_pin_data, [](void* args) { static_cast<Rotary*>(args)->encoderB(); }, this, GPIO_INTR_ANYEDGE);

    m_rotating = true;
    m_encoder_pos = 0;
    m_a_set = true;
    m_b_set = true;
}

void Rotary::loop()
{
    m_rotating = true;

    if (m_encoder_pos != 0)
    {
        if (auto currentDisplay = static_cast<const espgui::Display *>(espgui::currentDisplay.get()))
        {
            if (auto *menuDisplay = const_cast<espgui::MenuDisplay *>(currentDisplay->asMenuDisplay()))
            {
                menuDisplay->rotate(m_encoder_pos);
            }
        }

        m_encoder_pos = 0;
    }
}

std::array<Rotary, 4> rotary_encoders = {
    Rotary{ pins::ROTARY_1_CLK, pins::ROTARY_1_DATA },
    Rotary{ pins::ROTARY_2_CLK, pins::ROTARY_2_DATA },
    Rotary{ pins::ROTARY_3_CLK, pins::ROTARY_3_DATA },
    Rotary{ pins::ROTARY_4_CLK, pins::ROTARY_4_DATA },
};

void initRotary()
{
    if (const auto err = gpio_install_isr_service(0); err != ESP_OK)
        ESP_LOGE(TAG, "gpio_install_isr_service() failed: %s", esp_err_to_name(err));

    for (auto &rotary: rotary_encoders)
        rotary.begin();
}

void updateRotary()
{
    for (auto &rotary: rotary_encoders)
        rotary.loop();
}
} // namespace input

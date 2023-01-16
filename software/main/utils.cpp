#include "utils.h"

// esp-idf includes
#include <driver/gpio.h>
#include <esp_log.h>

namespace {
constexpr const char *const TAG = "ROTARY";
} // namespace

esp_err_t attachInterrupt(pin_t pin, void (*callback)(void *), void *arg, gpio_int_type_t type)
{
    esp_err_t result = ESP_OK;
    if (const auto err = gpio_set_intr_type((gpio_num_t)pin, type); err != ESP_OK)
    {
        ESP_LOGE(TAG, "gpio_set_intr_type() failed: %s", esp_err_to_name(err));
        result = err;
    }
    else
        ESP_LOGI(TAG, "gpio_set_intr_type() success");

    if (const auto err = gpio_isr_handler_add((gpio_num_t)pin, callback, arg); err != ESP_OK)
    {
        ESP_LOGE(TAG, "gpio_isr_handler_add() failed: %s", esp_err_to_name(err));
        if (result == ESP_OK)
            result = err;
    }
    else
        ESP_LOGI(TAG, "gpio_isr_handler_add() success");

    // enable interrupt on clk and data pin
    if (const auto err = gpio_intr_enable((gpio_num_t)pin); err != ESP_OK)
    {
        ESP_LOGE(TAG, "gpio_intr_enable() failed: %s", esp_err_to_name(err));
        if (result == ESP_OK)
            result = err;
    }
    else
        ESP_LOGI(TAG, "gpio_intr_enable() success");

    return result;
}

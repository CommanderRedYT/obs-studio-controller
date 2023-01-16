#pragma once

// esp-idf includes
#include <esp_err.h>
#include <hal/gpio_types.h>

// local includes
#include "pins.h"

esp_err_t attachInterrupt(pin_t pin, void (*callback)(void *), void *arg, gpio_int_type_t type);

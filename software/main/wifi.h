#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <tl/expected.hpp>

namespace wifi {
void wifi_init();
void wifi_update();
tl::expected<void, std::string> beginScan();
} // namespace wifi

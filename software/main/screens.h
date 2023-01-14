#pragma once

// system includes
#include <string_view>

namespace display {

void init();

void update();

void setBootMsg(std::string_view msg);

} // namespace display

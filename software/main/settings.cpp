#include "settings.h"

// 3rdparty lib includes
#include <espwifistack.h>

// local includes
#include "configmanager_priv.h"

namespace settings {

ConfigManager<ConfigContainer> configs;

std::string defaultHostname()
{
    if (const auto result = wifi_stack::get_default_mac_addr())
        return fmt::format("obsctrl_{:02x}{:02x}{:02x}", result->at(3), result->at(4), result->at(5));
    else
        ESP_LOGE(TAG, "get_default_mac_addr() failed: %.*s", result.error().size(), result.error().data());
    return "bobby";
}

} // namespace settings

INSTANTIATE_CONFIGMANAGER_TEMPLATES(settings::ConfigContainer);

#include "wifi.h"

// system includes
#include <optional>

// 3rdparty lib includes
#include <espwifistack.h>
#include <fmt/core.h>

// local includes
#include "settings.h"

namespace wifi {
namespace {
constexpr const char * const TAG = "WIFI";

wifi_stack::config createConfig();

std::optional<wifi_stack::sta_config> createStaConfig();

wifi_stack::wifi_entry createWiFiEntry(const WiFiConfig &config);

} // namespace

void wifi_init()
{
    wifi_stack::init(createConfig());
}

void wifi_update()
{
    wifi_stack::update(createConfig());
}

tl::expected<void, std::string> beginScan()
{
    const auto &staConfig = createStaConfig();
    if (!staConfig)
        return tl::make_unexpected("STA is not available");

    if (const auto result = wifi_stack::begin_scan(*staConfig); !result)
        return tl::make_unexpected(fmt::format("begin_scan failed: {}", result.error()));

    return {};
}

namespace {
wifi_stack::config createConfig()
{
    return wifi_stack::config{
        .base_mac_override = configs.baseMacAddressOverride.value(),
        .sta = createStaConfig(),
    };
}

std::optional<wifi_stack::sta_config> createStaConfig()
{
    if (!configs.wifiStaEnabled.value())
        return std::nullopt;

    return wifi_stack::sta_config{
        .hostname = configs.hostname.value(),
        .wifis = std::array<wifi_stack::wifi_entry, 10> {
            createWiFiEntry(configs.wifi_configs[0]),
            createWiFiEntry(configs.wifi_configs[1]),
            createWiFiEntry(configs.wifi_configs[2]),
            createWiFiEntry(configs.wifi_configs[3]),
            createWiFiEntry(configs.wifi_configs[4]),
            createWiFiEntry(configs.wifi_configs[5]),
            createWiFiEntry(configs.wifi_configs[6]),
            createWiFiEntry(configs.wifi_configs[7]),
            createWiFiEntry(configs.wifi_configs[8]),
            createWiFiEntry(configs.wifi_configs[9]),
        },
        .min_rssi = configs.wifiStaMinRssi.value(),
        .long_range = false,
    };
}

wifi_stack::wifi_entry createWiFiEntry(const WiFiConfig &wifi_config)
{
    std::optional<wifi_stack::static_ip_config> static_ip;
    if (wifi_config.useStaticIp.value())
        static_ip = wifi_stack::static_ip_config {
            .ip = wifi_config.staticIp.value(),
            .subnet = wifi_config.staticSubnet.value(),
            .gateway = wifi_config.staticGateway.value()
        };

    wifi_stack::static_dns_config static_dns;
    if (wifi_config.useStaticDns.value())
    {
        if (wifi_config.staticDns0.value().value())
            static_dns.main = wifi_config.staticDns0.value();
        if (wifi_config.staticDns1.value().value())
            static_dns.backup = wifi_config.staticDns1.value();
        if (wifi_config.staticDns2.value().value())
            static_dns.fallback = wifi_config.staticDns2.value();
    }

    return wifi_stack::wifi_entry {
        .ssid = wifi_config.ssid.value(),
        .key = wifi_config.pass.value(),
        .static_ip = static_ip,
        .static_dns = static_dns
    };
}

} // namespace
} // namespace wifi

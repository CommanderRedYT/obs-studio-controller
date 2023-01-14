#pragma once

// system includes
#include <array>
#include <optional>

// 3rdparty lib includes
#include <fmt/core.h>
#include <configmanager.h>
#include <configconstraints_base.h>
#include <configconstraints_espchrono.h>
#include <configwrapper.h>
#include <espchrono.h>
#include <espwifiutils.h>

// local includes
#include "enums.h"

using namespace espconfig;

#ifdef BOARD_REVISION_V1
#define DEFAULT_SCREEN_FLIP true
#else
#define DEFAULT_SCREEN_FLIP false
#endif

namespace settings {

std::string defaultHostname();

enum class AllowReset { NoReset, DoReset };
constexpr auto NoReset = AllowReset::NoReset;
constexpr auto DoReset = AllowReset::DoReset;

template<typename T>
class ConfigWrapperDynamicKey : public ConfigWrapper<T>
{
    CPP_DISABLE_COPY_MOVE(ConfigWrapperDynamicKey)
    using Base = ConfigWrapper<T>;

public:
    using value_t = typename Base::value_t;
    using ConstraintCallback = typename Base::ConstraintCallback;

    ConfigWrapperDynamicKey(const char *nvsName) : m_nvsName{nvsName} {}

    const char *nvsName() const override final { return m_nvsName; }

private:
    const char * const m_nvsName;
};

class WiFiConfig
{
public:
    WiFiConfig(const char *ssidNvsKey, const char *passNvsKey,
               const char *useStaticIpKey, const char *staticIpKey, const char *staticSubnetKey, const char *staticGatewayKey,
               const char *useStaticDnsKey, const char *staticDns0Key, const char *staticDns1Key, const char *staticDns2Key) :
       ssid{ssidNvsKey},
       pass{passNvsKey},
       useStaticIp{useStaticIpKey},
       staticIp{staticIpKey},
       staticSubnet{staticSubnetKey},
       staticGateway{staticGatewayKey},
       useStaticDns{useStaticDnsKey},
       staticDns0{staticDns0Key},
       staticDns1{staticDns1Key},
       staticDns2{staticDns2Key}
    {}

    struct : ConfigWrapperDynamicKey<std::string>
    {
        using ConfigWrapperDynamicKey<std::string>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        std::string defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return StringMaxSize<32>(value); }
    } ssid;
    struct : ConfigWrapperDynamicKey<std::string>
    {
        using ConfigWrapperDynamicKey<std::string>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        std::string defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return StringMaxSize<64>(value); }
    } pass;
    struct : ConfigWrapperDynamicKey<bool>
    {
        using ConfigWrapperDynamicKey<bool>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        bool defaultValue() const override final { return false; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } useStaticIp;
    struct : ConfigWrapperDynamicKey<wifi_stack::ip_address_t>
    {
        using ConfigWrapperDynamicKey<wifi_stack::ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        wifi_stack::ip_address_t defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } staticIp;
    struct : ConfigWrapperDynamicKey<wifi_stack::ip_address_t>
    {
        using ConfigWrapperDynamicKey<wifi_stack::ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        wifi_stack::ip_address_t defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } staticSubnet;
    struct : ConfigWrapperDynamicKey<wifi_stack::ip_address_t>
    {
        using ConfigWrapperDynamicKey<wifi_stack::ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        wifi_stack::ip_address_t defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } staticGateway;
    struct : ConfigWrapperDynamicKey<bool>
    {
        using ConfigWrapperDynamicKey<bool>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        bool defaultValue() const override final { return false; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } useStaticDns;
    struct : ConfigWrapperDynamicKey<wifi_stack::ip_address_t>
    {
        using ConfigWrapperDynamicKey<wifi_stack::ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        wifi_stack::ip_address_t defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } staticDns0;
    struct : ConfigWrapperDynamicKey<wifi_stack::ip_address_t>
    {
        using ConfigWrapperDynamicKey<wifi_stack::ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        wifi_stack::ip_address_t defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } staticDns1;
    struct : ConfigWrapperDynamicKey<wifi_stack::ip_address_t>
    {
        using ConfigWrapperDynamicKey<wifi_stack::ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const override final { return true; }
        wifi_stack::ip_address_t defaultValue() const override final { return {}; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } staticDns2;
};

class ConfigContainer;

extern ConfigManager<ConfigContainer> configs;

class ConfigContainer
{
    using mac_t = wifi_stack::mac_t;
    using ip_address_t = wifi_stack::ip_address_t;

public:
    struct : ConfigWrapper<std::optional<mac_t>>
    {
        bool allowReset() const override final { return false; }
        const char *nvsName() const override final { return "baseMacAddrOver"; }
        value_t defaultValue() const override final { return std::nullopt; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } baseMacAddressOverride;
    struct : ConfigWrapper<std::string>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "hostname"; }
        std::string defaultValue() const override final { return defaultHostname(); }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } hostname;
    struct : ConfigWrapper<bool>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "displayRot"; }
        value_t defaultValue() const override final { return DEFAULT_SCREEN_FLIP; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } displayRotated;
    struct : ConfigWrapper<bool>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "enable_sta"; }
        value_t defaultValue() const override final { return true; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } wifiStaEnabled;
    std::array<WiFiConfig, 10> wifi_configs {
        WiFiConfig{"wifi_ssid0", "wifi_pass0", "wifi_use_static_ip0", "wifi_static_ip0", "wifi_static_subnet0", "wifi_static_gateway0", "wifi_use_static_dns0", "wifi_static_dnsA0", "wifi_static_dnsB0", "wifi_static_dnsC0"},
        WiFiConfig{"wifi_ssid1", "wifi_pass1", "wifi_use_static_ip1", "wifi_static_ip1", "wifi_static_subnet1", "wifi_static_gateway1", "wifi_use_static_dns1", "wifi_static_dnsA1", "wifi_static_dnsB1", "wifi_static_dnsC1"},
        WiFiConfig{"wifi_ssid2", "wifi_pass2", "wifi_use_static_ip2", "wifi_static_ip2", "wifi_static_subnet2", "wifi_static_gateway2", "wifi_use_static_dns2", "wifi_static_dnsA2", "wifi_static_dnsB2", "wifi_static_dnsC2"},
        WiFiConfig{"wifi_ssid3", "wifi_pass3", "wifi_use_static_ip3", "wifi_static_ip3", "wifi_static_subnet3", "wifi_static_gateway3", "wifi_use_static_dns3", "wifi_static_dnsA3", "wifi_static_dnsB3", "wifi_static_dnsC3"},
        WiFiConfig{"wifi_ssid4", "wifi_pass4", "wifi_use_static_ip4", "wifi_static_ip4", "wifi_static_subnet4", "wifi_static_gateway4", "wifi_use_static_dns4", "wifi_static_dnsA4", "wifi_static_dnsB4", "wifi_static_dnsC4"},
        WiFiConfig{"wifi_ssid5", "wifi_pass5", "wifi_use_static_ip5", "wifi_static_ip5", "wifi_static_subnet5", "wifi_static_gateway5", "wifi_use_static_dns5", "wifi_static_dnsA5", "wifi_static_dnsB5", "wifi_static_dnsC5"},
        WiFiConfig{"wifi_ssid6", "wifi_pass6", "wifi_use_static_ip6", "wifi_static_ip6", "wifi_static_subnet6", "wifi_static_gateway6", "wifi_use_static_dns6", "wifi_static_dnsA6", "wifi_static_dnsB6", "wifi_static_dnsC6"},
        WiFiConfig{"wifi_ssid7", "wifi_pass7", "wifi_use_static_ip7", "wifi_static_ip7", "wifi_static_subnet7", "wifi_static_gateway7", "wifi_use_static_dns7", "wifi_static_dnsA7", "wifi_static_dnsB7", "wifi_static_dnsC7"},
        WiFiConfig{"wifi_ssid8", "wifi_pass8", "wifi_use_static_ip8", "wifi_static_ip8", "wifi_static_subnet8", "wifi_static_gateway8", "wifi_use_static_dns8", "wifi_static_dnsA8", "wifi_static_dnsB8", "wifi_static_dnsC8"},
        WiFiConfig{"wifi_ssid9", "wifi_pass9", "wifi_use_static_ip9", "wifi_static_ip9", "wifi_static_subnet9", "wifi_static_gateway9", "wifi_use_static_dns9", "wifi_static_dnsA9", "wifi_static_dnsB9", "wifi_static_dnsC9"}
    };
    struct : ConfigWrapper<int8_t>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "sta_min_rssi"; }
        value_t defaultValue() const override final { return -127; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } wifiStaMinRssi;

    template<typename T>
    void callForEveryConfig(T &&callable)
    {
#define REGISTER_CONFIG(name) \
    if (callable(name)) return;

        REGISTER_CONFIG(baseMacAddressOverride);
        REGISTER_CONFIG(hostname);
        REGISTER_CONFIG(displayRotated);
    }
};

} // namespace settings

using namespace settings;

#include "wificolor.h"

std::string rssiToColor(int8_t rssi)
{
         if (rssi < -80) return "&1"; // red
    else if (rssi < -70) return "&4"; // yellow
    else if (rssi > -40) return "&2"; // green
    return {};
}

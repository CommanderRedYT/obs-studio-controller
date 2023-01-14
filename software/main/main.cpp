constexpr const char * const TAG = "MAIN";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <screenmanager.h>

// local includes
#include "screens.h"
#include "settings.h"
#include "taskmanager.h"

extern "C" void app_main()
{
    using namespace display;

    if (const auto result = configs.init("config"); result != ESP_OK)
        ESP_LOGE(TAG, "configs.init() failed: %s", esp_err_to_name(result));

    display::init();

    for (auto &task : schedulerTasks)
    {
        ESP_LOGI(TAG, "Starting task %s", task.name());
        setBootMsg(task.name());
        task.setup();
    }

    while (true)
    {
        for (auto &task : schedulerTasks)
            task.loop();

        vTaskDelay(1);
    }
}

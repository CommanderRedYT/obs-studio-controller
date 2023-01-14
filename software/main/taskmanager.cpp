#include "taskmanager.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "screens.h"

using namespace std::chrono_literals;

namespace {
using namespace espcpputils;

constexpr const char * const TAG = "TASKMANAGER";

void noop() {}

SchedulerTask schedulerTaskArr[] {
    SchedulerTask{ "display_update", noop, display::update, 30ms },
};
} // namespace

cpputils::ArrayView<SchedulerTask> schedulerTasks{std::begin(schedulerTaskArr), std::end(schedulerTaskArr)};

void sched_pushStats(bool printTasks)
{
    if (printTasks)
        ESP_LOGI(TAG, "Task stats:");

    for (auto &task : schedulerTasks)
        task.pushStats(printTasks);
}

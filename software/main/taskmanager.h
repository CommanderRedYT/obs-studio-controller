#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <arrayview.h>
#include <schedulertask.h>

extern cpputils::ArrayView<espcpputils::SchedulerTask> schedulerTasks;

void sched_pushStats(bool printTasks);

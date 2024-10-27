#pragma once
#include <libs/common/types.h>

struct cpuvar;
#include <arch_types.h>

#define CPUVAR_MAGIC 0xbeefbeef
#define CPUVAR       (arch_cpuvar_get())

struct task;

struct cpuvar {
    struct arch_cpuvar arch;
    int id;
    bool online;
    unsigned ipi_pending;
    struct task *idle_task;
    struct task *current_task;
    unsigned magic;
};

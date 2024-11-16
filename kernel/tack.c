#include "task.h"
#include <libs/common/list.h>

static struct task tasks[NUM_TASKS_MAX];        // 全てのタスク管理構造体 (未使用含む)
static struct task idle_tasks[NUM_CPUS_MAX];    // 各CPUのアイドルタスク
static list_t runqueue = LIST_INIT(runqueue);   // ランキュー
list_t active_tasks = LIST_INIT(active_tasks);  // 使用中の管理構造体のリスト

// 次に実行するタスクを選択する。
static struct task *scheduler(void) {
    // ランキューから実行可能なタスクを取り出す。
    struct task *next = LIST_POP_FRONT(&runqueue, struct task, waitqueue_next);
    if (next) {
        return next;
    }

    if (CURRENT_TASK->state == TASK_RUNNABLE && !CURRENT_TASK->destroyed) {
        // 他に実行可能なタスクがない場合は、実行中タスクを続行する。
        return CURRENT_TASK;
    }

    return IDLE_TASK;  // 実行するタスクがない場合はアイドルタスクを実行する。
}

// 自発的なタスク切り替えを行う。もし実行可能なタスクが実行中タスク以外にない場合は、即座に
// 戻ってくる。その他の場合は、他のタスクに実行が移され、次回タスクが再びスケジュールされたとき
// に戻ってくる。
// Bennoスケジューリング（実行可能タスクのみ入れる = CURRENT_TASKは「返信待ちで実行できない状態のタスク」の可能性があるので含まない。
//                   実行可能だけじゃない曖昧な状態だとLazyスケジューリングする必要があり、タスク数に比例して時間がかかる。)
void task_switch(void) {
    struct task *prev = CURRENT_TASK;  // 実行中タスク
    struct task *next = scheduler();   // 次に実行するタスク

    // 次に実行するタスクにCPU時間を与える
    // 実行を継続したとしても、クォンタムは明確に区切る
    if (next != IDLE_TASK) {
        next->quantum = TASK_QUANTUM;
    }

    if (next == prev) {
        // 実行中タスク以外に実行可能なタスクがない。戻って処理を続ける。
        return;
    }

    if (prev->state == TASK_RUNNABLE) {
        // 実行中タスクが実行可能な状態ならば、実行可能なタスクのキューに戻す。
        // 与えられたCPU時間を使い切ったときに起きる。
        list_push_back(&runqueue, &prev->waitqueue_next);
    }

    // タスクを切り替える
    CURRENT_TASK = next;
    arch_task_switch(prev, next);
}

// タスクをブロック状態にする。実行中タスク自身をブロックする場合は、task_switch関数を
// 呼び出して他のタスクに実行を移す必要がある。
void task_block(struct task *task) {
    DEBUG_ASSERT(task != IDLE_TASK);
    DEBUG_ASSERT(task->state == TASK_RUNNABLE);

    task->state = TASK_BLOCKED;
}

// タスクを実行可能状態にする。
void task_resume(struct task *task) {
    DEBUG_ASSERT(task->state == TASK_BLOCKED);

    task->state = TASK_RUNNABLE;
    list_push_back(&runqueue, &task->waitqueue_next);
}

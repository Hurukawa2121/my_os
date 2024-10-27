#include "task.h"
#include <libs/common/list.h>

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

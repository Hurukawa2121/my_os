#include "asm.h"
#include <kernel/arch.h>

// 次のタスク (next) に切り替える。prevには現在実行中のタスクを指定する。
void arch_task_switch(struct task *prev, struct task *next) {
    // ハードウェアからの割り込みハンドラやシステムコールで使うカーネルスタック(CPUローカル変数)を切り替える。
    // システムコールハンドラ内でスリープ状態に入ることがあるため、タスクごとに実行コンテキスト
    // を保持する専用のカーネルスタックが必要。
    CPUVAR->arch.sp_top = next->arch.sp_top;

    // ページテーブルを切り替えてTLBをフラッシュする。satpレジスタに書き込む前に一度
    // sfence.vma命令を実行しているのは、ここ以前に行ったページテーブルへの変更が
    // 完了するのを保証するため。
    // (The RISC-V Instruction Set Manual Volume II, Version 1.10, p. 58)
    asm_sfence_vma();
    write_satp(SATP_MODE_SV32 | next->vm.table >> SATP_PPN_SHIFT);
    asm_sfence_vma();

    // この時点では、スタックポインタ（spレジスタ）は以前として実行タスク(prev)のまま

    // 汎用レジスタをスタックに対比し、次のタスク (next) をレジスタにロードし実行を移す。
    // このタスク (prev) は実行コンテキストが保存され、再度続行されるときはこの関数から
    // 帰ってきたように振る舞う。
    riscv32_task_switch(&prev->arch.sp, &next->arch.sp);
}

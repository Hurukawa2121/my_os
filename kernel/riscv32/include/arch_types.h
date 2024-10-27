#pragma once
#include <libs/common/type.h>

// 仮想アドレス空間上のカーネルメモリ領域の開始アドレス。
#define KERNEL_BASE 0x80000000
// IRQの最大数。
#define IRQ_MAX 32

// RISC-V特有のタスク管理構造体。
struct arch_task {
    uint32_t sp;        // 次回実行時に復元されるべきカーネルスタックの値
    uint32_t sp_top;    // カーネルスタックの上端
    paddr_t sp_bottom;  // カーネルスタックの底
};

// RISC-V特有のページテーブル管理構造体。
struct arch_vm {
    paddr_t table;  // ページテーブルの物理アドレス (Sv32)
};


// RISC-V特有のCPUローカル変数。順番を変える時はasmdefs.hで定義しているマクロも更新する。
struct arch_cpuvar {
    uint32_t sscratch;  // 変数の一時保管場所
    uint32_t sp_top;    // 実行中タスクのカーネルスタックの上端

    // タイマー割り込みハンドラ (M-mode) で使用。
    uint32_t mscratch0;   // 変数の一時保管場所
    uint32_t mscratch1;   // 変数の一時保管場所その2
    paddr_t mtimecmp;     // MTIMECMPのアドレス
    paddr_t mtime;        // MTIMEのアドレス
    uint32_t interval;    // MTIMECMPに加算していく値
    uint64_t last_mtime;  // 直前のmtimeの値
};

// CPUVARマクロの中身。現在のCPUローカル変数のアドレスを返す。
static inline struct cpuvar *arch_cpuvar_get(void) {
    // tpレジスタにCPUローカル変数のアドレスが格納されている。
    uint32_t tp;
    __asm__ __volatile__("mv %0, tp" : "=r"(tp));
    return (struct cpuvar *) tp;
}

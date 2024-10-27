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

// CPUVARマクロの中身。現在のCPUローカル変数のアドレスを返す。
static inline struct cpuvar *arch_cpuvar_get(void) {
    // tpレジスタにCPUローカル変数のアドレスが格納されている。
    uint32_t tp;
    __asm__ __volatile__("mv %0, tp" : "=r"(tp));
    return (struct cpuvar *) tp;
}

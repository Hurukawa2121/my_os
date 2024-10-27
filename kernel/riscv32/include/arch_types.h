#pragma once
#include <libs/common/type.h>

struct arch_task {
    uint32_t sp;        // 次回実行時に復元されるべきカーネルスタックの値
    uint32_t sp_top;    // カーネルスタックの上端
    paddr_t sp_bottom;  // カーネルスタックの底
};


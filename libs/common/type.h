#pragma once
#include "buildconfig.h"

typedef char int8_t;                  //  8ビット符号付き整数型
typedef short int16_t;                // 16ビット符号付き整数型
typedef int int32_t;                  // 32ビット符号付き整数型
typedef long long int64_t;            // 64ビット符号付き整数型
typedef unsigned char uint8_t;        // 8ビット符号なし整数型
typedef unsigned short uint16_t;      // 16ビット符号なし整数型
typedef unsigned uint32_t;            // 32ビット符号なし整数型
typedef unsigned long long uint64_t;  // 64ビット符号なし整数型

#if !defined(__LP64__) // 64 ビットのコンパイル・モードが有効なら
// intの最大値
#    define INT_MAX 2147483647
// unsigned intの最大値
#    define UINT_MAX 4294967295U
// 符号付き整数型の最大値
typedef int32_t intmax_t;
// 符号なし整数型の最大値
typedef uint32_t uintmax_t;
#endif

// 真偽値
typedef char bool;
#define true  1
#define false 0

// ヌルポインタ
#define NULL ((void *) 0)

typedef int error_t;               // エラーコードを表す整数型
typedef int task_t;                // タスクID
typedef int handle_t;              // ハンドルID
typedef uint32_t notifications_t;  // 通知を表すビットフィールド

typedef uintmax_t size_t;          // 大きさを表す整数型
typedef long pfn_t;                // 物理ページ番号を表す整数型
typedef uintmax_t paddr_t;         // 物理アドレスを表す整数型
typedef uintmax_t vaddr_t;         // 仮想アドレスを表す整数型
typedef uintmax_t uaddr_t;         // ユーザー空間の仮想アドレスを表す整数型
typedef uintmax_t uintptr_t;       // ポインタが指すアドレスを格納する整数型
typedef uintmax_t offset_t;        // オフセットを表す整数型

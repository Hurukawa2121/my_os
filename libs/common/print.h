// printf関数のラッパーマクロ。カーネル・ユーザーランド両方で利用できるように定義されている。
#pragma once

// アサーション。exprが偽ならエラーメッセージを出力してプログラムを終了する。
#define ASSERT(expr)                                                           \
    do {                                                                       \
        if (!(expr)) {                                                         \
            panic_before_hook();                                               \
            printf(SGR_ERR                                                     \
                   "[%s] %s:%d: ASSERTION FAILURE: %s" SGR_RESET PRINT_NL,     \
                   __program_name(), __FILE__, __LINE__, #expr);               \
            backtrace();                                                       \
            panic_after_hook();                                                \
            __builtin_unreachable();                                           \
        }                                                                      \
    } while (0)

// デバッグ用アサーション。デバッグビルド時のみ有効になる。
#ifdef DEBUG_BUILD
#    define DEBUG_ASSERT(expr) ASSERT(expr)
#else
#    define DEBUG_ASSERT(expr) ((void) (expr))
#endif

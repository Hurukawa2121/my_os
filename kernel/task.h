


// タスク管理構造体
struct task {
    struct arch_task arch;          // CPU依存のタスク情報
    struct arch_vm vm;              // ページテーブル
    task_t tid;                     // タスクID
    char name[TASK_NAME_LEN];       // タスク名
    int state;                      // タスクの状態
    bool destroyed;                 // タスクが削除されている途中かどうか
    struct task *pager;             // ページャータスク
    unsigned timeout;               // タイムアウトの残り時間
    int ref_count;                  // タスクが参照されている数 (ゼロでないと削除不可)
    unsigned quantum;               // タスクの残りクォンタム
    list_elem_t waitqueue_next;     // 各種待ちリストの次の要素へのポインタ
    list_elem_t next;               // 全タスクリストの次の要素へのポインタ
    list_t senders;                 // このタスクへの送信待ちタスクリスト
    task_t wait_for;                // このタスクへメッセージ送信ができるタスクID
                                    // (IPC_ANYの場合は全て)
    list_t pages;                   // 利用中メモリページのリスト
    notifications_t notifications;  // 受信済みの通知
    struct message m;               // メッセージの一時保存領域
};
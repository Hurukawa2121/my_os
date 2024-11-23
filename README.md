勉強用

```md
├── fs              # ディスクイメージ（HinaFS）の内容
├── kernel          # マイクロカーネル
│   └── riscv32     # ハードウェア抽象化レイヤ（32ビット RISC-V CPU 特有の処理）
├── libs            # ライブラリ
│   ├── common      # カーネル・ユーザーランド共通ライブラリ
│   └── user        # ユーザーランド用ライブラリ
├── servers         # サーバ・アプリケーション
│   ├── fs          # ファイルシステムサーバ
│   ├── shell       # コマンドラインシェル
│   ├── tcpip       # TCP/IP サーバ
│   ├── virtio_blk  # ストレージデバイスドライバ（virtio-blk デバイス）
│   ├── virtio_net  # ネットワークデバイスドライバ（virtio-net デバイス）
│   ├── vm          # タスク・メモリ管理サーバ
└── tools           # ビルド時に使われるツール
```

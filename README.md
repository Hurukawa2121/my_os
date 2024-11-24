勉強用

```md
├── fs                # HinaFSの内容
├── kernel            # カーネル
│   └── riscv32       # カーネルのCPUアーキテクチャ依存部分 (32ビットRISC-V用)
├── libs              # ライブラリ
│   ├── common        # カーネル・ユーザーランド共通のライブラリ
│   │   └── riscv32   # commonライブラリのCPUアーキテクチャ依存部分 (32ビットRISC-V用)
│   └── user          # ユーザーランド用ライブラリ
│       ├── riscv32   # userライブラリのCPUアーキテクチャ依存部分 (32ビットRISC-V用)
│       └── virtio    # virtioデバイスドライバのためのライブラリ
├── mk                # ビルドシステム関連
├── servers           # サーバ・アプリケーション
│   ├── crack         # HinaOSの脆弱性を実証するプログラム
│   ├── fs            # HinaFSファイルシステムサーバ
│   ├── hello         # Hello Worldを表示するプログラム
│   ├── hello_hinavm  # HinaVM上でサンプルプログラム (pongサーバ) を起動するプログラム
│   ├── pong          # pongサーバ (シェルのpingコマンドの通信先)
│   ├── shell         # コマンドラインシェル
│   ├── tcpip         # TCP/IPサーバ
│   ├── virtio_blk    # virtio-blk ストレージデバイスドライバ
│   ├── virtio_net    # virtio-net ネットワークデバイスドライバ
│   └── vm            # VMサーバ: メモリ管理、タスク管理など (最初に起動するサーバ)
└── tools             # 雑多なビルド・開発用スクリプト
```

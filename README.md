# MICS 実験 B2 (ラウンド 4) テーマ C

MICS 実験 B2 (ラウンド 4) テーマ C 「ハッシュを使った類似検索」

## プロジェクト構成

C++で実装。テストには googletest を使用

```
mics-r4/
├── src/           # メインソースコード
│   └── chainhash.cc    # ハッシュテーブルの実装
├── tools/         # 開発ツール
│   └── mnistview/      # MNIST画像ビューワー
├── tests/         # テストコード
├── data/          # データファイル
└── include/       # ヘッダーファイル
```

## 依存関係

- [OpenCV](https://opencv.org/) 4.x
- CMake 3.14+
- C++17
- googletest 1.17.x

(タスクランナーとして[task](https://github.com/go-task/task)の導入を推奨)

## 開発補助ツール

### mnistview

MNIST データセットの画像を可視化するための開発用ツール。

```bash
# ビルド
task tools:mnistview:build

# 実行例
task tools:mnistview:run -- ./data/test-images.txt
```

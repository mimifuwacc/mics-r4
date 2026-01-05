cmake_minimum_required(VERSION 3.14)
project(mics-r4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCVの検索
find_package(OpenCV REQUIRED)

# Google Testの有効化（テスト時のみ）
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# まだGoogle Testを利用しない場合はコメントアウト
# FetchContent_MakeAvailable(googletest)

# ソースファイルの設定
set(SOURCES
    src/chainhash.cc
)

# ヘッダーファイルのインクルードパス
include_directories(${OpenCV_INCLUDE_DIRS})

# 実行ファイルのビルド
add_executable(chainhash src/chainhash.cc)
target_link_libraries(chainhash ${OpenCV_LIBS})

# テスト（有効化する場合はコメントを外す）
# enable_testing()
# add_executable(chainhash_test tests/chainhash_test.cc)
# target_link_libraries(chainhash_test gtest_main gmock_main)

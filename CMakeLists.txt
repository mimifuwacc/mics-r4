cmake_minimum_required(VERSION 3.14)
project(mics-r4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# コンパイラフラグの設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# OpenCVの検索
find_package(OpenCV REQUIRED)

# Google Testの有効化
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# ソースファイルの設定
set(SOURCES
    src/chainhash.cc
)

# ヘッダーファイルのインクルードパス
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# 実行ファイルのビルド
add_executable(main src/chainhash.cc src/main.cc)
target_link_libraries(main ${OpenCV_LIBS})

# テスト
enable_testing()

add_executable(chainhash_test tests/chainhash_test.cc src/chainhash.cc)
target_link_libraries(chainhash_test gtest gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(chainhash_test)

cmake_minimum_required(VERSION 3.14)
project(mics-r4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# コンパイラフラグの設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Google Testの有効化
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# ソースファイルの自動検出
file(GLOB SOURCES "src/*.cc")
file(GLOB_RECURSE HEADERS "include/*.h")

# ヘッダーファイルのインクルードパス
include_directories(${CMAKE_SOURCE_DIR}/include)

# 実行ファイルのビルド
file(GLOB SRC_FILES "src/*.cc")

# main.cc を除外して、他のすべてのソースファイルをリンク
list(FILTER SRC_FILES EXCLUDE REGEX ".*main\\.cc$")
add_executable(main src/main.cc ${SRC_FILES})

# テスト
enable_testing()

include(GoogleTest)

# テストファイルを自動検出
file(GLOB TEST_SOURCES "tests/*_test.cc")
file(GLOB SRC_FILES "src/*.cc")

# main.cc を除外
list(FILTER SRC_FILES EXCLUDE REGEX ".*main\\.cc$")

foreach(test_source ${TEST_SOURCES})
  get_filename_component(test_name ${test_source} NAME_WE)
  add_executable(${test_name} ${test_source} ${SRC_FILES})
  target_link_libraries(${test_name} gtest gmock gtest_main)

  # テストを自動検出（テスト名の前に実行ファイル名を付加）
  gtest_discover_tests(${test_name}
    TEST_PREFIX "${test_name}."
  )
endforeach()

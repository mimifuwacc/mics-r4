cmake_minimum_required(VERSION 3.14)
project(mnistview)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# コンパイラフラグの設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# OpenCVの検索
find_package(OpenCV REQUIRED)

# ヘッダーファイルのインクルードパス
include_directories(${OpenCV_INCLUDE_DIRS})

# 実行ファイルのビルド
add_executable(mnistview main.cc)

# macOSでGUIを動作させるために必要なフレームワーク
if(APPLE)
  target_link_libraries(mnistview
    ${OpenCV_LIBS}
    "-framework Cocoa"
  )
else()
  target_link_libraries(mnistview ${OpenCV_LIBS})
endif()

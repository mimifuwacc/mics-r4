#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include "loadmnist.h"

using namespace std;

// split関数のテスト
TEST(MnistDbTest, SplitFunction) {
  // 基本的な分割テスト
  string test1 = " 0 1 2 3 4";
  vector<int> result1;
  split(test1, ' ', result1);
  EXPECT_EQ(result1.size(), 5);
  EXPECT_EQ(result1[0], 0);
  EXPECT_EQ(result1[1], 1);
  EXPECT_EQ(result1[4], 4);

  // 最初が空白の場合
  string test2 = " 10 20 30";
  vector<int> result2;
  split(test2, ' ', result2);
  EXPECT_EQ(result2.size(), 3);
  EXPECT_EQ(result2[0], 10);
  EXPECT_EQ(result2[1], 20);
  EXPECT_EQ(result2[2], 30);

  // MNIST風のデータ（0と非0が混在）
  string test3 = " 0 0 255 0 128 0 0";
  vector<int> result3;
  split(test3, ' ', result3);
  EXPECT_EQ(result3.size(), 7);
  EXPECT_EQ(result3[0], 0);
  EXPECT_EQ(result3[2], 255);
  EXPECT_EQ(result3[4], 128);
}

// テスト用一時ファイルを作成してloadMnistをテスト
class LoadMnistTest : public ::testing::Test {
 protected:
  string test_file;

  void SetUp() override {
    // テスト用一時ファイルを作成（プロセスIDとunixtimeを含めて一意にする）
    char template_buf[256];
    snprintf(template_buf, sizeof(template_buf),
             "/tmp/mics-r4_mnistdb_test_%d_%ld", getpid(), time(nullptr));
    test_file = template_buf;
    int fd = mkstemp(&test_file[0]);
    if (fd == -1) {
      FAIL() << "Failed to create temp file";
    }
    close(fd);
  }

  void TearDown() override {
    // テスト終了時に一時ファイルを削除
    remove(test_file.c_str());
  }

  void writeTestData(const vector<string>& lines) {
    ofstream fp(test_file);
    if (!fp.is_open()) {
      FAIL() << "Failed to open test file: " << test_file;
    }
    for (const auto& line : lines) {
      fp << line << endl;
    }
    fp.close();
  }
};

TEST_F(LoadMnistTest, LoadSingleImage) {
  // 28x28のテスト画像（非ゼロが3つ）
  string test_line;
  for (int i = 0; i < 784; i++) {
    if (i == 2 || i == 29 || i == 56) {  // (0,2), (1,1), (2,0)
      test_line += " 255";
    } else {
      test_line += " 0";
    }
  }
  writeTestData({test_line});

  MnistDatabase db;
  loadMnist(test_file, db);

  EXPECT_EQ(db.size(), 1);
  EXPECT_EQ(db[0].size(), 3);
  EXPECT_EQ(db[0][0], 2);   // (0,2) -> 0*28+2 = 2
  EXPECT_EQ(db[0][1], 29);  // (1,1) -> 1*28+1 = 29
  EXPECT_EQ(db[0][2], 56);  // (2,0) -> 2*28+0 = 56
}

TEST_F(LoadMnistTest, LoadMultipleImages) {
  // 2枚の28x28画像
  string line1, line2;
  for (int i = 0; i < 784; i++) {
    if (i == 0 || i == 29 || i == 58) {  // (0,0), (1,1), (2,2)
      line1 += " 255";
    } else {
      line1 += " 0";
    }
    if (i == 2 || i == 29 || i == 56) {  // (0,2), (1,1), (2,0)
      line2 += " 255";
    } else {
      line2 += " 0";
    }
  }
  writeTestData({line1, line2});

  MnistDatabase db;
  loadMnist(test_file, db);

  EXPECT_EQ(db.size(), 2);

  // 1枚目の画像
  EXPECT_EQ(db[0].size(), 3);
  EXPECT_EQ(db[0][0], 0);   // (0,0)
  EXPECT_EQ(db[0][1], 29);  // (1,1)
  EXPECT_EQ(db[0][2], 58);  // (2,2)

  // 2枚目の画像
  EXPECT_EQ(db[1].size(), 3);
  EXPECT_EQ(db[1][0], 2);   // (0,2)
  EXPECT_EQ(db[1][1], 29);  // (1,1)
  EXPECT_EQ(db[1][2], 56);  // (2,0)
}

TEST_F(LoadMnistTest, LoadAllZeroImage) {
  // 全てゼロの28x28画像
  string line;
  for (int i = 0; i < 784; i++) {
    line += " 0";
  }
  writeTestData({line});

  MnistDatabase db;
  loadMnist(test_file, db);

  EXPECT_EQ(db.size(), 1);
  EXPECT_EQ(db[0].size(), 0);
}

TEST_F(LoadMnistTest, Load28x28Image) {
  // 28x28の全て非ゼロ画像（最初と最後のピクセルのみ確認）
  string line;
  for (int i = 0; i < 784; i++) {
    line += " " + to_string(255);
  }
  writeTestData({line});

  MnistDatabase db;
  loadMnist(test_file, db);

  EXPECT_EQ(db.size(), 1);
  EXPECT_EQ(db[0].size(), 784);
  EXPECT_EQ(db[0][0], 0);      // 最初のピクセル
  EXPECT_EQ(db[0][783], 783);  // 最後のピクセル
}

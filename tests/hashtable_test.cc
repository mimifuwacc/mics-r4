#include <gtest/gtest.h>
#include "hashtable.h"

// myhash関数のテスト
TEST(HashTest, BasicHashing) {
  EXPECT_EQ(myhash(10, 10), 0);
  EXPECT_EQ(myhash(15, 10), 5);
  EXPECT_EQ(myhash(100, 10), 0);
  EXPECT_EQ(myhash(99, 100), 99);
}

TEST(HashTest, EdgeCases) {
  EXPECT_EQ(myhash(0, 10), 0);
  EXPECT_EQ(myhash(1, 1), 0);
}

TEST(HashTest, LargeValues) {
  EXPECT_EQ(myhash(1000000, 100), 0);
  EXPECT_EQ(myhash(12345, 100), 45);
  EXPECT_EQ(myhash(UINT32_MAX, 100), 95);
}

TEST(HashTest, Consistency) {
  // 同じ入力には同じハッシュ値が返る
  EXPECT_EQ(myhash(42, 10), myhash(42, 10));
  EXPECT_EQ(myhash(42, 10), myhash(42 + 10, 10));
  EXPECT_EQ(myhash(42, 10), myhash(42 + 100, 10));
}

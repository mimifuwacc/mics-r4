#include <gtest/gtest.h>
#include "openhash.h"
#include <cstdint>

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

// insertとsearchのテスト
TEST(HashTableTest, InsertAndSearch) {
  OpenHashTable table;
  table.table_size = 10;
  table.buckets.resize(10);

  // データを挿入
  insert(5, table);
  insert(15, table);
  insert(25, table);

  // 検索
  EXPECT_TRUE(search(5, table));
  EXPECT_TRUE(search(15, table));
  EXPECT_TRUE(search(25, table));
  EXPECT_FALSE(search(35, table));
}

TEST(HashTableTest, MultipleItemsSameBucket) {
  OpenHashTable table;
  table.table_size = 10;
  table.buckets.resize(10);

  // 同じハッシュ値（余りが5）になるデータを挿入
  insert(5, table);
  insert(15, table);
  insert(25, table);
  insert(35, table);

  // すべて検索可能（線形探査で配置される）
  EXPECT_TRUE(search(5, table));
  EXPECT_TRUE(search(15, table));
  EXPECT_TRUE(search(25, table));
  EXPECT_TRUE(search(35, table));
}

TEST(HashTableTest, EmptyTable) {
  OpenHashTable table;
  table.table_size = 10;
  table.buckets.resize(10);

  // 空のテーブルでは何も見つからない
  EXPECT_FALSE(search(5, table));
  EXPECT_FALSE(search(0, table));
}

TEST(HashTableTest, LargeDataset) {
  OpenHashTable table;
  table.table_size = 200;
  table.buckets.resize(200);

  // 多数のデータを挿入（テーブルサイズ以下）
  for (uint i = 0; i < 150; i++) {
    insert(i, table);
  }

  // いくつか検索
  EXPECT_TRUE(search(0, table));
  EXPECT_TRUE(search(50, table));
  EXPECT_TRUE(search(149, table));
  EXPECT_FALSE(search(150, table));
}

TEST(HashTableTest, TableFull) {
  OpenHashTable table;
  table.table_size = 10;
  table.buckets.resize(10);

  // テーブルサイズと同じ数のデータを挿入
  for (uint i = 0; i < 10; i++) {
    insert(i * 10, table);  // すべて同じハッシュ値0になるデータ
  }

  // すべて検索可能
  for (uint i = 0; i < 10; i++) {
    EXPECT_TRUE(search(i * 10, table));
  }
}

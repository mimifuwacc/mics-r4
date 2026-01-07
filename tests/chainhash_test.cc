#include <gtest/gtest.h>
#include "chainhash.h"

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
  ChainHashTable table;
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
  ChainHashTable table;
  table.table_size = 10;
  table.buckets.resize(10);

  // 同じバケットに複数のデータを挿入（10で割った余りが同じ）
  insert(1, table);
  insert(11, table);
  insert(21, table);
  insert(31, table);

  // すべて検索可能
  EXPECT_TRUE(search(1, table));
  EXPECT_TRUE(search(11, table));
  EXPECT_TRUE(search(21, table));
  EXPECT_TRUE(search(31, table));
}

TEST(HashTableTest, EmptyTable) {
  ChainHashTable table;
  table.table_size = 10;
  table.buckets.resize(10);

  // 空のテーブルでは何も見つからない
  EXPECT_FALSE(search(5, table));
  EXPECT_FALSE(search(0, table));
}

TEST(HashTableTest, LargeDataset) {
  ChainHashTable table;
  table.table_size = 100;
  table.buckets.resize(100);

  // 多数のデータを挿入
  for (uint i = 0; i < 1000; i++) {
    insert(i, table);
  }

  // いくつか検索
  EXPECT_TRUE(search(0, table));
  EXPECT_TRUE(search(500, table));
  EXPECT_TRUE(search(999, table));
  EXPECT_FALSE(search(1000, table));
}

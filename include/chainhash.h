#ifndef CHAINHASH_H_
#define CHAINHASH_H_

#include <vector>
#include <cstdint>

typedef uint32_t uint;
typedef uint Item;

// ハッシュバケツ
typedef struct Bucket {
  std::vector<Item> Items;
} Bucket;

// ハッシュテーブル
typedef struct HashTable {
  uint table_size;              // テーブルサイズ
  std::vector<Bucket> buckets;  // バケツの配列
} HashTable;

typedef std::vector<Item> Database;

// ハッシュ関数　tablesizeで割った余りをハッシュ値とする
uint myhash(Item i, uint tablesize);

// ハッシュテーブルへの挿入
void insert(Item data, HashTable& table);

// ハッシュテーブルからの探索
bool search(Item query, HashTable& table);

#endif  // CHAINHASH_H_

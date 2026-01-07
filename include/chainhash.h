#ifndef CHAINHASH_H_
#define CHAINHASH_H_

#include "hashtable.h"
#include <vector>

// チェイン法用のバケツ
struct ChainBucket {
  std::vector<Item> Items;
};

// チェイン法用のハッシュテーブル
using ChainHashTable = HashTable<ChainBucket>;

// ハッシュテーブルへの挿入
void insert(Item data, ChainHashTable& table);

// ハッシュテーブルからの探索
bool search(Item query, ChainHashTable& table);

#endif  // CHAINHASH_H_

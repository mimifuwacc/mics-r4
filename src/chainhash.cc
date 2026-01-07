#include "chainhash.h"

// ハッシュテーブルへの挿入
void insert(Item data, ChainHashTable& table) {
  uint index = myhash(data, table.table_size);
  table.buckets[index].Items.push_back(data);
}

// ハッシュテーブルからの探索
bool search(Item query, ChainHashTable& table) {
  uint index = myhash(query, table.table_size);

  bool isfound = false;

  for (uint i = 0; i < table.buckets[index].Items.size(); i++)
    if (table.buckets[index].Items[i] == query)
      isfound = true;

  return isfound;
}

#ifndef OPENHASH_H_
#define OPENHASH_H_

#include "hashtable.h"
#include <vector>

// 開番地法用のバケツ
struct OpenBucket {
  Item data;     // データ
  bool isempty;  // 空き状態を表すフラグ

  // コンストラクタで初期化
  OpenBucket() : data(0), isempty(true) {}
};

// 開番地法用のハッシュテーブル
using OpenHashTable = HashTable<OpenBucket>;

// ハッシュテーブルへの挿入
void insert(Item data, OpenHashTable& table);

// ハッシュテーブルからの探索
bool search(Item query, OpenHashTable& table);

#endif  // OPENHASH_H_

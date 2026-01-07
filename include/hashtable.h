#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <vector>
#include <cstdint>

typedef uint32_t uint;
typedef uint Item;

// ハッシュ関数　tablesizeで割った余りをハッシュ値とする
uint myhash(Item i, uint tablesize);

// ハッシュテーブルのテンプレート
template <typename BucketType>
struct HashTable {
  uint table_size;
  std::vector<BucketType> buckets;
};

#endif  // HASHTABLE_H_

#include "openhash.h"

void insert(Item data, OpenHashTable& table) {
  uint index = myhash(data, table.table_size);

  for (uint i = 0; i < table.table_size; i++) {
    uint current_index = (index + i) % table.table_size;

    if (table.buckets[current_index].isempty) {
      table.buckets[current_index].data = data;
      table.buckets[current_index].isempty = false;
      return;
    }

    if (table.buckets[current_index].data == data) {
      return;  // すでに存在する場合は挿入しない
    }
  }
  // テーブルが満杯の場合は何もしない
}

bool search(Item query, OpenHashTable& table) {
  uint index = myhash(query, table.table_size);

  for (uint i = 0; i < table.table_size; i++) {
    uint current_index = (index + i) % table.table_size;

    if (table.buckets[current_index].isempty) {
      return false;  // 空き場所に到達したら存在しない
    }

    if (table.buckets[current_index].data == query) {
      return true;  // 見つかった
    }
  }
  return false;  // テーブル全体を探索したが見つからなかった
}

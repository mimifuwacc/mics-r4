#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef unsigned int uint;
typedef uint Item;

// ハッシュバケツ
typedef struct Bucket {
  // uint hash_value; //後に使用する
  vector<Item> Items;
} Bucket;

// ハッシュテーブル
typedef struct HashTable {
  uint table_size;         // テーブルサイズ
  vector<Bucket> buckets;  // バケツの配列
} HashTable;

typedef vector<Item> Database;

// ハッシュ関数　tablesizeで割った余りをハッシュ値とする
uint myhash(Item i, uint tablesize) {
  return i % tablesize;
}

// ハッシュテーブルへの挿入
void insert(Item data, HashTable& table) {
  uint index = myhash(data, table.table_size);
  table.buckets[index].Items.push_back(data);
}

// ハッシュテーブルからの探索
bool search(Item query, HashTable& table) {
  uint index = myhash(query, table.table_size);

  bool isfound = false;

  for (uint i = 0; i < table.buckets[index].Items.size(); i++)
    if (table.buckets[index].Items[i] == query)
      isfound = true;

  return isfound;
}

int main(int argc, char* argv[]) {
  HashTable tab;
  uint i;

  // ハッシュテーブルサイズ
  uint table_size = atoi(argv[1]);

  // ハッシュテーブル初期化
  tab.table_size = table_size;
  tab.buckets.resize(table_size);  // bucketsの要素数を設定

  // for(i=0;i<table_size;i++){ //後に使用する
  //   tab.buckets[i].hash_value = 0xffffffff;
  //  }

  Database db;
  // データベースの要素数
  uint dbsize = atoi(argv[2]);

  // データベース生成
  for (i = 0; i < dbsize; i++) {
    bool isnewitem = false;
    Item cand;
    // 二重登録しないための確認
    do {
      uint j;
      cand = rand() % 10000;
      for (j = 0; j < db.size(); j++)
        if (db[j] == cand)
          break;

      if (j == db.size())
        isnewitem = true;
    } while (isnewitem == false);

    db.push_back(cand);
  }

  for (i = 0; i < db.size(); i++)
    cout << db[i] << endl;

  // データのハッシュテーブルへの登録
  for (i = 0; i < db.size(); i++) {
    insert(db[i], tab);
  }

  // 検索処理
  Item query =
      db[rand() % db.size()];  // データベースの要素をquery(検索対象)に選ぶ

  if (search(query, tab))
    cout << "query exists in the database " << endl;
  else
    cout << "query does not exist in the database " << endl;

  return 0;
}

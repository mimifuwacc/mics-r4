#include <iostream>
#include <cstdlib>
#include "chainhash.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " <table_size> <db_size>" << endl;
    return 1;
  }

  HashTable tab;
  uint i;

  // ハッシュテーブルサイズ
  uint table_size = atoi(argv[1]);

  // ハッシュテーブル初期化
  tab.table_size = table_size;
  tab.buckets.resize(table_size);  // bucketsの要素数を設定

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

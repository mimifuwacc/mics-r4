#ifndef MNISTDB_H_
#define MNISTDB_H_

#include <string>
#include <vector>
#include "hashtable.h"

typedef std::vector<std::vector<Item>> MnistDatabase;

// 文字列を区切り文字で分割し、数値群に変換して返す関数
void split(const std::string& str, char sep, std::vector<int>& v);

// MNISTデータを読み込み、MnistDatabaseに格納する関数
void loadMnist(const std::string& filename, MnistDatabase& db);

#endif  // MNISTDB_H_

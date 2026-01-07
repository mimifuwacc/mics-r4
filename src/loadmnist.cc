#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include "loadmnist.h"

using namespace std;

// 文字列を区切り文字で分割し、数値群に変換して返す関数
void split(const string& str, char sep, vector<int>& v) {
  stringstream ss(str);
  int num;
  int i = 0;

  string buffer;
  while (getline(ss, buffer, sep)) {
    if (i > 0) {           // 最初の空文字列をスキップ
      num = stoi(buffer);  // 文字列を数値に変換
      v.push_back(num);    // ベクトルvに追加
    }
    i++;
  }
}

// MNISTデータを読み込み、MnistDatabaseに格納する関数
void loadMnist(const string& filename, MnistDatabase& db) {
  ifstream fp(filename);

  if (!fp.is_open()) {
    cerr << "Error: Cannot open file " << filename << endl;
    exit(1);
  }

  // ファイルの行数をカウント（画像数を取得）
  int line_count = 0;
  string buf;
  while (getline(fp, buf)) {
    line_count++;
  }

  // ファイルポインタを先頭に戻す
  fp.clear();
  fp.seekg(0, ios::beg);

  // MnistDatabaseのサイズを確保
  db.resize(line_count);

  // 各画像を読み込み、集合表現に変換
  int img_idx = 0;
  while (getline(fp, buf) && (img_idx < line_count)) {
    vector<int> pixels;
    split(buf, ' ', pixels);

    // 非ゼロ画素の位置を収集
    vector<Item> positions;
    for (int row = 0; row < 28; row++) {
      for (int col = 0; col < 28; col++) {
        int pixel_idx = row * 28 + col;
        if (pixels[pixel_idx] != 0) {
          positions.push_back(static_cast<Item>(pixel_idx));
        }
      }
    }

    db[img_idx] = positions;
    img_idx++;
  }

  fp.close();
}

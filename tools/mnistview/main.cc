#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

#define TRAIN_IMG_NUM (1000) // 読み込む画像数

using namespace std;

vector<int> split(const string &str, char sep) // 文字列strを区切り文字sepで分割し、数値群に変換して返す
{
  vector<int> v;
  stringstream ss(str);
  int num;
  int i = 0;

  string buffer;
  while (getline(ss, buffer, sep))
  {
    if (i > 0)
    {
      num = stoi(buffer); // 文字列を数値に変換
      v.push_back(num);   // ベクトルvに追加
    }
    i++;
  }
  return v;
}

int main(int argc, char **argv)
{

  string train_image_name = "/home3/staff/ka109040/.ced_centos/MICS/test-images.txt";

  ifstream fp(argv[1]);
  string buf; // ファイル名を格納する文字列
  vector<int> contents;
  int i = 0;

  cv::Mat Img(28, 28, CV_32FC1); // 表示用の画像(を表す行列)
  while (getline(fp, buf) && (i < TRAIN_IMG_NUM))
  {                             // 1画像読み込み
    contents = split(buf, ' '); // 読み込んだ内容を分解
    for (int j = 0; j < 784; j++)
    {
      Img.at<float>(j / 28, j % 28) = contents[j]; // 表示用画像を構築
    }
    cv::namedWindow("train_image", cv::WINDOW_AUTOSIZE);
    cv::imshow("train_image", Img);
    cv::waitKey(0);
    i++;
  }

  fp.close();
  return 0;
}

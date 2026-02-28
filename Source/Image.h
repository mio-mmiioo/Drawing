#pragma once
#include "Play/Area.h"
#include <map>
#include <string>

namespace Image
{
	void Init();
	void MakeImage(area a, int* hImage); // aの範囲を画像データとしてhImageに代入する
	extern std::map<std::string, int> hImage; // 画像データ
}
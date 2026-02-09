#pragma once
#include <string>
#include <map>
#include <vector>

#include "Play/Area.h"

namespace Data
{
	void Init();

	extern std::map<std::string, area> areaList; // エリアのリスト
	extern std::map<std::string, button> buttonList; // ボタンのリスト
}

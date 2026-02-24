#pragma once
#include <string>
#include <map>
#include <vector>

#include "Play/Area.h"
#include "MyLibrary/Client.h"

namespace Data
{
	void Init();

	extern std::map<std::string, area> areaList; // エリアのリスト
	extern std::map<std::string, button> buttonList; // ボタンのリスト

	Client* GetClient();
}

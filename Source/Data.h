#pragma once
#include <string>
#include <map>
#include <vector>

#include "Play/Area.h"
#include "MyLibrary/Client.h"

namespace Data
{
	void Init();

	void SendData(std::string message, int number); // サーバーにデータを送る
	bool isStartPlay(); // プレイ画面に遷移してよいか
	bool isStartMatching(); // マッチング画面に遷移してよいか


	extern std::map<std::string, area> areaList; // エリアのリスト
	extern std::map<std::string, button> buttonList; // ボタンのリスト

	static int roomNumber; // ポート番号
	static std::string clientName; // ユーザーの名前

	Client* GetClient();
}

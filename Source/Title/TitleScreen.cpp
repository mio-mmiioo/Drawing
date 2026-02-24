#include "TitleScreen.h"
#include "DxLib.h"
#include "../Play/Area.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "../Data.h"
#include "../Scene.h"

namespace TitleScreen
{
	button makeRoom; // 部屋を立てるボタン
	button enterRoom; // 入室ボタン
	button rule; // ルール確認ボタン

	point mouse; // マウス
	PACKET sendData;

	int roomNumber; // 部屋番号
}


void TitleScreen::Init()
{
	makeRoom = { Data::areaList["b-MakeRoom"], Data::areaList["c-MakeRoom"], false};
	enterRoom = { Data::areaList["b-EnterRoom"], Data::areaList["c-EnterRoom"], false };
	rule = { Data::areaList["b-Rule"], Data::areaList["c-Rule"], false };

	sendData = { "", "", -1 }; // ここ気に食わない
	roomNumber = 0000;
}

void TitleScreen::Update()
{
	GetMousePoint(&mouse.x, &mouse.y);
	if (Input::IsKeyDown("ok"))
	{
		Area::IsClickArea(makeRoom.bArea, mouse, &makeRoom.isClickArea);
		Area::IsClickArea(enterRoom.bArea, mouse, &enterRoom.isClickArea);
		Area::IsClickArea(rule.bArea, mouse, &rule.isClickArea);
	}

	// 部屋立ち上げ、入室のいずれかのボタンが押された場合、サーバーにデータを送る
	{
		if (makeRoom.isClickArea == true)
		{
			const char dataType[] = "MAKE_ROOM";
			strncpy_s(sendData.dataType, sizeof(sendData.dataType), dataType, _TRUNCATE);
			sendData.hImage = roomNumber;
			Data::GetClient()->SetClient(sendData);
			Data::GetClient()->SendData();
			SceneMaster::ChangeScene("MATCHING");

		}
		if (enterRoom.isClickArea == true)
		{
			const char dataType[] = "ENTER_ROOM";
			strncpy_s(sendData.dataType, sizeof(sendData.dataType), dataType, _TRUNCATE);
			sendData.hImage = roomNumber;
			Data::GetClient()->SetClient(sendData);
			Data::GetClient()->SendData();
			SceneMaster::ChangeScene("MATCHING");
		}
	}
}

void TitleScreen::Draw()
{
	Area::DrawButton2(makeRoom, Color::MAKE_ROOM);
	Area::DrawButton2(enterRoom, Color::ENTER_ROOM);
	Area::DrawButton1(rule, Color::RULE);
}

void TitleScreen::Release()
{
}

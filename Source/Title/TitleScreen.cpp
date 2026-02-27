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
}


void TitleScreen::Init()
{
	makeRoom = { Data::areaList["b-MakeRoom"], Data::areaList["c-MakeRoom"], false};
	enterRoom = { Data::areaList["b-EnterRoom"], Data::areaList["c-EnterRoom"], false };
	rule = { Data::areaList["b-Rule"], Data::areaList["c-Rule"], false };
}

void TitleScreen::Update()
{
	Data::GetClient()->ReceiveData();
	GetMousePoint(&mouse.x, &mouse.y);
	if (Input::IsKeyDown("ok"))
	{
		Area::IsClickArea(makeRoom.bArea, mouse, &makeRoom.isClickArea);
		Area::IsClickArea(enterRoom.bArea, mouse, &enterRoom.isClickArea);
		Area::IsClickArea(rule.bArea, mouse, &rule.isClickArea);
	}

	// 部屋立ち上げ、入室のいずれかのボタンが押された場合、サーバーにデータを送る
	{
		std::string message;
		if (makeRoom.isClickArea == true)
		{
			message = "MAKE_ROOM";
			Data::SendData(message, Data::roomNumber);
		}
		if (enterRoom.isClickArea == true)
		{
			message = "ENTER_ROOM";
			Data::SendData(message, Data::roomNumber);
		}

		PACKET recvData = Data::GetClient()->GetReciveData();
		if (Data::isStartMatching() == true)
		{
			SceneMaster::ChangeScene("MATCHING");
			WaitTimer(50);
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

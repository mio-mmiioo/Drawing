#include "MatchingScreen.h"
#include "../MyLibrary/Area.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "../Data.h"
#include "../Scene.h"

namespace MatchingScreen
{
	button endMakeRoom; // ゲーム開始ボタン
	button changeName;	// 名前変更ボタン

	point mouse;
}

void MatchingScreen::Init()
{
	endMakeRoom = { Data::areaList["b-EndMakeRoom"], Data::areaList["c-EndMakeRoom"], false };
	changeName = { Data::areaList["b-ChangeName"], Data::areaList["c-ChangeName"], false };
}

void MatchingScreen::Update()
{
	Data::GetClient()->ReceiveData();

	GetMousePoint(&mouse.x, &mouse.y);
	if (Input::IsKeyDown("ok"))
	{
		Area::SetClickArea(endMakeRoom.bArea, mouse, &endMakeRoom.isClickArea);
		Area::SetClickArea(changeName.bArea, mouse, &changeName.isClickArea);
	}

	if (endMakeRoom.isClickArea == true)
	{
		Data::SendData("END_MAKE_ROOM", Data::roomNumber); // サーバーに報告
	}
	if (changeName.isClickArea == true)
	{
		Data::SendData("CHANGE_NAME", Data::roomNumber);
	}

	if (Data::isStartPlay() == true)
	{
		SceneMaster::ChangeScene("PLAY"); // 画面遷移
	}
}

void MatchingScreen::Draw()
{
	Area::DrawButton2(endMakeRoom, Color::END_MAKE_ROOM);
	Area::DrawButton2(changeName, Color::CHANGE_NAME);
}

void MatchingScreen::Release()
{
}

#include "MatchingScreen.h"
#include "../Play/Area.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "../Data.h"
#include "../Scene.h"

namespace MatchingScreen
{
	int hImage;

	button endMakeRoom;
	button changeName;

	point mouse;
}

void MatchingScreen::Init()
{
	hImage = 0;
	endMakeRoom = { Data::areaList["b-EndMakeRoom"], Data::areaList["c-EndMakeRoom"], false };
	changeName = { Data::areaList["b-ChangeName"], Data::areaList["c-ChangeName"], false };
}

void MatchingScreen::Update()
{
	Data::GetClient()->ReceiveData();

	GetMousePoint(&mouse.x, &mouse.y);
	if (Input::IsKeyDown("ok"))
	{
		Area::IsClickArea(endMakeRoom.bArea, mouse, &endMakeRoom.isClickArea);
		Area::IsClickArea(changeName.bArea, mouse, &changeName.isClickArea);
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

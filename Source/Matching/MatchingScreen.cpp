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

	point mouse;
}

void MatchingScreen::Init()
{
	hImage = 0;
	endMakeRoom = { Data::areaList["b-EndMakeRoom"], Data::areaList["c-EndMakeRoom"], false };
}

void MatchingScreen::Update()
{
	GetMousePoint(&mouse.x, &mouse.y);
	if (Input::IsKeyDown("ok"))
	{
		Area::IsClickArea(endMakeRoom.bArea, mouse, &endMakeRoom.isClickArea);
	}

	if (endMakeRoom.isClickArea == true)
	{
		Data::SendData("END_MAKE_ROOM", Data::portNumber); // サーバーに報告
		SceneMaster::ChangeScene("PLAY"); // 画面遷移
	}
}

void MatchingScreen::Draw()
{
	Area::DrawButton2(endMakeRoom, Color::END_MAKE_ROOM);
}

void MatchingScreen::Release()
{
}

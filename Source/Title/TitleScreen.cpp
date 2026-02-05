#include "TitleScreen.h"
#include "DxLib.h"
#include "../Play/Area.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"

namespace TitleScreen
{
	button makeRoom; // 部屋を立てるボタン
	button enterRoom; // 入室ボタン
	button rule; // ルール確認ボタン

	point mouse; // マウス
}


void TitleScreen::Init()
{
	makeRoom = { 200, 500, 300, 550, 190, 490, 310, 560, false };
	enterRoom = { 400, 500, 500, 550, 390, 490, 510, 560, false };
	rule = { 900, 50, 950, 100, 100, 50, 900, 650, false };
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

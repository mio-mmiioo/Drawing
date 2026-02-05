#include "TitleScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"

#include "TitleScreen.h"

TitleScene::TitleScene()
{
	TitleScreen::Init();
}

TitleScene::~TitleScene()
{
	TitleScreen::Release();
}

void TitleScene::Update()
{
	TitleScreen::Update();
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("PLAY");
	}
}

void TitleScene::Draw()
{
	TitleScreen::Draw();
	DrawFormatString(10, 10, Color::TEXT, "Title Scene");
}

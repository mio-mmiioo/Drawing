#include "TitleScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("PLAY");
	}
}

void TitleScene::Draw()
{
	DrawFormatString(10, 10, Color::TEXT, "Title Scene");
}

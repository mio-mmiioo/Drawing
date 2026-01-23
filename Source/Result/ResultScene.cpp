#include "ResultScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	DrawFormatString(10, 10, Color::TEXT, "ResultScene");
}

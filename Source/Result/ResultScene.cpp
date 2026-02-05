#include "ResultScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"

#include "ResultScreen.h"

ResultScene::ResultScene()
{
	ResultScreen::Init();
}

ResultScene::~ResultScene()
{
	ResultScreen::Release();
}

void ResultScene::Update()
{
	ResultScreen::Update();
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	ResultScreen::Draw();
	DrawFormatString(10, 10, Color::TEXT, "ResultScene");
}

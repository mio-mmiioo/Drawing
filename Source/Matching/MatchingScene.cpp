#include "MatchingScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"
#include "MatchingScreen.h"

MatchingScene::MatchingScene()
{
	MatchingScreen::Init();
}

MatchingScene::~MatchingScene()
{
	MatchingScreen::Release();
}

void MatchingScene::Update()
{
	MatchingScreen::Update();
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("PLAY");
	}
}

void MatchingScene::Draw()
{
	MatchingScreen::Draw();
	DrawFormatString(10, 10, Color::TEXT, "Matching Scene");
}

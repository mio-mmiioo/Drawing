#include "MatchingScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"

MatchingScene::MatchingScene()
{
}

MatchingScene::~MatchingScene()
{
}

void MatchingScene::Update()
{
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("PLAY");
	}
}

void MatchingScene::Draw()
{
	DrawFormatString(10, 10, Color::TEXT, "Matching Scene");
}

#include "PlayScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	DrawFormatString(10, 10, Color::TEXT, "PlayScene");
}

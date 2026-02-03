#include "PlayScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"
#include "Player.h"

PlayScene::PlayScene()
{
	Player::Init();
}

PlayScene::~PlayScene()
{
	Player::Release();
}

void PlayScene::Update()
{
	Player::Update();
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	Player::Draw();
}

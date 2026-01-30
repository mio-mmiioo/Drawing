#include "PlayScene.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Input.h"
#include "Player.h"
#include "Phase.h"

PlayScene::PlayScene()
{
	Player::Init();
	Phase::Init(3);
}

PlayScene::~PlayScene()
{
	Player::Release();
}

void PlayScene::Update()
{
	Player::Update();
	Phase::Update();
	if (Input::IsKeyDown("nextScene"))
	{
		SceneMaster::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	Player::Draw();
	Phase::Draw();
}

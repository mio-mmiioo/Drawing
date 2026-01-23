#include "Scene.h"
#include "Title/TitleScene.h"
#include "Play/PlayScene.h"
#include "Result/ResultScene.h"

namespace SceneMaster
{
	Scene* current;
}

void SceneMaster::CreateFirst()
{
	current = new TitleScene();
}

void SceneMaster::ChangeScene(const std::string& name)
{
	if (name == "TITLE")
	{
		current = new TitleScene();
	}
	else if (name == "PLAY")
	{
		current = new PlayScene();
	}
	else if (name == "RESULT")
	{
		current = new ResultScene();
	}
	else
	{
		// ƒV[ƒ“‚ªØ‚è‘Ö‚í‚ç‚È‚¢
	}
}

void SceneMaster::Init()
{
}

void SceneMaster::Update()
{
	current->Update();
}

void SceneMaster::Draw()
{
	current->Draw();
}

void SceneMaster::Release()
{
	current->~Scene();
}


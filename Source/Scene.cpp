#include "Scene.h"
#include "../ImGui/imgui.h"

// 各シーン
#include "Title/TitleScene.h"
#include "Play/PlayScene.h"
#include "Result/ResultScene.h"

namespace SceneMaster
{
	void ImGuiInput();

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
		// シーンが切り替わらない
	}
}

void SceneMaster::Init()
{
}

void SceneMaster::Update()
{
	ImGuiInput();
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

void SceneMaster::ImGuiInput()
{
	ImGui::Begin("SceneMaster");
	ImGui::Text("test");
	ImGui::End();
}


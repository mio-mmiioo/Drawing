#include "Phase.h"
#include "../MyLibrary/Time.h"
#include "../../ImGui/imgui.h"

namespace Phase
{
	enum P_STATE
	{
		THEME, // お題入力
		DRAWING, // お絵描き
		WAITE, // 待ち時間
		MAX_P_STATE
	};

	const float THEME_TIME = 60.0f; // お題入力 60秒
	const float DRAWING_TIME = 180.0f; // お絵描き 180秒

	int phaseMax; // 「お題」「お絵描き」を繰り返す回数
	int phaseCount; // 何回「お題」「お絵描き」を繰り返しているか
	float timer; // 各フェーズの時間をはかる
	P_STATE state; // ゲームのどの段階か
}

void Phase::Init(int peopleNumber)
{
	phaseMax = peopleNumber;
	phaseCount = 0;
	timer = THEME_TIME;
	state = THEME;
}

void Phase::Update()
{
	switch (state)
	{
	case P_STATE::THEME:
		break;
	case P_STATE::DRAWING:
		break;
	case P_STATE::WAITE:
		return;
		break;
	}

	if (state != P_STATE::WAITE)
	{
		timer -= Time::DeltaTime();
	}

	if (timer <= 0.0f)
	{
		phaseCount += 1;
		if (phaseCount % 2 == 0)
		{
			timer += THEME_TIME;
		}
		else
		{
			timer += DRAWING_TIME;
		}
	}
}

void Phase::Draw()
{
	// タイマーの表示
	//ImGui::Begin("Phase");
	//ImGui::Text("timer:%f", timer);
	//ImGui::End();
}

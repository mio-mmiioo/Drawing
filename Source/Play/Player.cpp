#include "Player.h"
#include "DxLib.h"
#include "../../ImGui/imgui.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "Pen.h"
#include "Area.h"
#include <vector>

namespace Player
{
	void ImGuiInput();

	std::vector<std::vector<point>> drawLine; // 線の位置情報
	std::vector<int> drawLineColor; // 線の色の情報
	std::vector<float> drawLineWidth; // 線の太さの情報
	int lineCount; // 絵に描かれている線の数
	float lineWidth; // ペンの太さ
	point mouse; // マウスの座標
	bool isCanUsePen; // true → ペンが使用可能 


	int penColor; // ペンの色
}

void Player::Init()
{
	lineCount = 0;
	lineWidth = 10.0f;
	GetMousePoint(&mouse.x, &mouse.y);
	isCanUsePen = false;

	Pen::Init();
	Pen::SetColor(&penColor);
}

void Player::Update()
{
	isCanUsePen = false;
	GetMousePoint(&mouse.x, &mouse.y);
	Pen::SetMousePosition(mouse);

	Pen::IsCanUse(&isCanUsePen);
	
	//ImGuiInput();

	// 1つ戻る
	if (Input::IsKeyDown("back") && drawLine.size() > 0)
	{
		drawLine.pop_back();
		lineCount -= 1;
	}
	// 色を変更する 機能の実装はまだ
	if (Input::IsKeyDown("changeColor"))
	{
		Pen::ChangeColor(&penColor);
	}
	// 消しゴム
	if (Input::IsKeyDown("eraser"))
	{
		Pen::Erase(&penColor);
	}
	// 線の太さを変更する 
	if (Input::IsKeyDown("changeWidth"))
	{
		Pen::ChangeWidth(&lineWidth);
	}


	// 線を描く
	if (isCanUsePen == true)
	{
		if (Input::IsKeyDown("drawing"))
		{
			std::vector<point> tmp;
			tmp.push_back(mouse);
			drawLine.push_back(tmp);
			drawLineColor.push_back(penColor);
			drawLineWidth.push_back(lineWidth);
		}
		else if (Input::IsKeyKeepDown("drawing"))
		{
			drawLine[lineCount].push_back(mouse);
		}
		else if (Input::IsKeyUp("drawing"))
		{
			lineCount += 1;
		}
	}


}

void Player::Draw()
{
	Pen::Draw();
	Pen::DrawChangePenWidth(lineWidth);
	// これまでに描いた線を描画
	{
		int x;
		int y;
		int nextX;
		int nextY;
		int c;
		float lineW;

		for (int l = 0; l < drawLine.size(); l++)
		{
			c = drawLineColor[l];
			lineW = drawLineWidth[l];
			for (int p = 0; p < drawLine[l].size() - 1; p++)
			{
				x = drawLine[l][p].x;
				y = drawLine[l][p].y;
				nextX = drawLine[l][p + 1].x;
				nextY = drawLine[l][p + 1].y;

				// 線or丸のみだと、不自然な描画になってしまうため、どちらも描画
				DrawLine(x, y, nextX, nextY, c, lineW);	
				DrawCircle(x, y, lineW / 2, c, TRUE);
			}
		}
	}
}

void Player::Release()
{
	drawLine.clear();
}

void Player::ImGuiInput()
{
	//ImGui::Begin("Player");
	//ImGui::InputFloat("lineWidth", &lineWidth);
	//ImGui::Checkbox("Erase", &eraser.isClickArea);
	//ImGui::End();
}


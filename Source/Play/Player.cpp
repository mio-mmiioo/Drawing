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

	button changeColor; // 色を変更
	button changeWidth; // 線の幅を変更
	button eraser; // 消しゴム
	int penRed; // ペンの赤色の値
	int penGreen; // ペンの緑色の値
	int penBlue; // ペンの青色の値
	int penColor; // ペンの色
}

void Player::Init()
{
	lineCount = 0;
	lineWidth = 10.0f;
	GetMousePoint(&mouse.x, &mouse.y);
	isCanUsePen = false;

	eraser = { 0, 0, 100, 100, false };
	changeWidth = { 120, 0, 220, 100, false };
	changeColor = { 240, 0, 340, 100, false };
	penRed = 0;
	penGreen = 0;
	penBlue = 0;
	penColor = GetColor(penRed, penGreen, penBlue);
}

void Player::Update()
{
	isCanUsePen = false;
	GetMousePoint(&mouse.x, &mouse.y);
	
	//ImGuiInput();

	// 1つ戻る
	if (Input::IsKeyDown("back") && drawLine.size() > 0)
	{
		drawLine.pop_back();
		lineCount -= 1;
	}
	// 色を変更する 機能の実装はまだ
	if (Input::IsKeyDown("changeColor") && Area::IsInArea(changeColor, mouse) == true)
	{
		if (changeColor.isClickArea == true)
		{
			changeColor.isClickArea = false;
		}
		else
		{
			changeColor.isClickArea = true;
		}
	}
	// 消しゴム
	if (Input::IsKeyDown("eraser") && Area::IsInArea(eraser, mouse) == true)
	{
		if (eraser.isClickArea == true)
		{
			eraser.isClickArea = false;
			penColor = GetColor(penRed, penGreen, penBlue);
		}
		else
		{
			eraser.isClickArea = true;
			penColor = Color::ERASER;
		}
	}
	// 線の太さを変更する 
	if (Input::IsKeyDown("changeWidth") && Area::IsInArea(changeWidth, mouse) == true)
	{
		if (changeWidth.isClickArea == true)
		{
			changeWidth.isClickArea = false;
		}
		else
		{
			changeWidth.isClickArea = true;
		}
	}


	// 線を描く
	{
		point current = { mouse.x, mouse.y };
		if (Input::IsKeyDown("drawing"))
		{
			std::vector<point> tmp;
			tmp.push_back(current);
			drawLine.push_back(tmp);
			drawLineColor.push_back(penColor);
			drawLineWidth.push_back(lineWidth);
		}
		else if (Input::IsKeyKeepDown("drawing"))
		{
			drawLine[lineCount].push_back(current);
		}
		else if (Input::IsKeyUp("drawing"))
		{
			lineCount += 1;
		}
	}


}

void Player::Draw()
{
	Pen::DrawCanvas();

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

	// エリアを描画
	Area::DrawButton(changeColor, Color::AREA);
	Area::DrawButton(eraser, Color::AREA);
	Area::DrawButton(changeWidth, Color::AREA);
	if (changeColor.isClickArea == true)
	{
		DrawCircle(100, 500, 20, Color::CHANGE_CIRCLE, TRUE); // 確認のために描画
	}
	if (changeWidth.isClickArea == true)
	{
		Pen::DrawChangePenWidth(lineWidth);
	}
}

void Player::Release()
{
	drawLine.clear();
}

void Player::ImGuiInput()
{
	ImGui::Begin("Player");
	ImGui::InputFloat("lineWidth", &lineWidth);
	ImGui::End();
}


#include "Player.h"
#include "DxLib.h"
#include "../../ImGui/imgui.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "Pen.h"
#include <vector>

namespace Player
{
	struct point
	{
		int x;
		int y;
	};

	struct button
	{
		point leftTop; // 左上の座標
		point rightDown; // 右下の座標
		bool isClickArea; // true → ボタンをクリックした
	};

	void ImGuiInput();
	bool IsInArea(button b); // 引数で渡したボタン上にマウスがある
	void DrawButton(button b, int buttonColor); // ボタンの範囲を描画 開発時のみしか使用しない可能性あり

	std::vector<std::vector<point>> drawLine; // 線の位置情報
	std::vector<int> drawLineColor; // 線の色の情報
	std::vector<float> drawLineWidth; // 線の太さの情報
	int lineCount; // 絵に描かれている線の数
	float lineWidth; // ペンの太さ
	point mouse; // マウスの座標

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
	lineWidth = 40.0f;
	GetMousePoint(&mouse.x, &mouse.y);

	eraser = { 0, 0, 100, 100, false };
	changeWidth = { 120, 0, 220, 100, false };
	changeColor = { 240, 0, 340, 100, false };
	penRed = 255;
	penGreen = 255;
	penBlue = 255;
	penColor = GetColor(penRed, penGreen, penBlue);
}

void Player::Update()
{
	GetMousePoint(&mouse.x, &mouse.y);
	
	//ImGuiInput();

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

	// 1つ戻る
	if (Input::IsKeyDown("back") && drawLine.size() > 0)
	{
		drawLine.pop_back();
		lineCount -= 1;
	}

	// 色を変更する 機能の実装はまだ
	if (Input::IsKeyDown("changeColor") && IsInArea(changeColor) == true)
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
	if (Input::IsKeyDown("eraser") && IsInArea(eraser) == true)
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
	if (Input::IsKeyDown("changeWidth") && IsInArea(changeWidth) == true)
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
}

void Player::Draw()
{
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
				DrawLine(x, y, nextX, nextY, c, lineW);
			}
		}
	}

	// エリアを描画
	DrawButton(changeColor, Color::AREA);
	DrawButton(eraser, Color::AREA);
	DrawButton(changeWidth, Color::AREA);
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

bool Player::IsInArea(button b)
{
	if (b.leftTop.x < mouse.x && mouse.x < b.rightDown.x)
	{
		if (b.leftTop.y < mouse.y && mouse.y < b.rightDown.y)
		{
			return true;
		}
	}
	return false;
}

void Player::DrawButton(button b, int buttonColor)
{
	int x1 = b.leftTop.x;
	int y1 = b.leftTop.y;
	int x2 = b.rightDown.x;
	int y2 = b.rightDown.y;
	DrawBox(x1, y1, x2, y2, buttonColor, TRUE);
}

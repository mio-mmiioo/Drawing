#include "Player.h"
#include "DxLib.h"
#include "../../ImGui/imgui.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include <vector>

namespace Player
{
	struct point
	{
		int x;
		int y;
	};

	struct drawPoint
	{
		point p; // 座標
		int color; // 色
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

	std::vector<std::vector<drawPoint>> drawLine; // 絵の情報
	int lineCount; // 絵に描かれている線の数
	float lineWidth; // ペンの太さ
	point mouse; // マウスの座標

	button changeColor; // 色を変更する場所
	button eraser; // 消しゴム
	int penRed; // ペンの赤色の値
	int penGreen; // ペンの緑色の値
	int penBlue; // ペンの青色の値
	int penColor; // ペンの色
}

void Player::Init()
{
	lineCount = 0;
	lineWidth = 5.0f;
	GetMousePoint(&mouse.x, &mouse.y);

	eraser = { 0, 0, 100, 100, false };
	changeColor = { 120, 0, 220, 100, false };
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
		drawPoint current = { mouse.x, mouse.y, penColor };
		if (Input::IsKeyDown("drawing"))
		{
			std::vector<drawPoint> tmp;
			tmp.push_back(current);
			drawLine.push_back(tmp);
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

		for (int l = 0; l < drawLine.size(); l++)
		{
			for (int p = 0; p < drawLine[l].size() - 1; p++)
			{
				x = drawLine[l][p].p.x;
				y = drawLine[l][p].p.y;
				nextX = drawLine[l][p + 1].p.x;
				nextY = drawLine[l][p + 1].p.y;
				c = drawLine[l][p].color;
				DrawLine(x, y, nextX, nextY, c, lineWidth);
			}
		}
	}

	// エリアを描画
	DrawButton(changeColor, Color::AREA);
	DrawButton(eraser, Color::AREA);
	if (changeColor.isClickArea == true)
	{
		DrawCircle(100, 500, 20, Color::CHANGE_CIRCLE, TRUE); // 確認のために描画
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

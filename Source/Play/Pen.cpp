#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"
#include <vector>

namespace Pen
{
	const area CHANGE_PEN_WIDTH = { 80, 100, 120, 340 }; // ペンの太さを変更する場所
	const point WIDTH_LINE_TOP = { 100, 120 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 100, 320 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 2.0f; // ペンの太さ変更線の太さ

	const area CANVAS = { 50, 50, 650, 550 }; // 絵が描ける範囲

	
	button changeColor; // 色を変更
	button changeWidth; // 線の幅を変更
	button eraser; // 消しゴム

	point pMouse; // playerのマウスの座標

	std::vector<area> drawAreaList;

	int penRed; // ペンの赤色の値
	int penGreen; // ペンの緑色の値
	int penBlue; // ペンの青色の値
}

void Pen::Init()
{
	eraser = { 0, 0, 100, 100, false };
	changeWidth = { 120, 0, 220, 100, false };
	changeColor = { 240, 0, 340, 100, false };

	penRed = 0;
	penGreen = 100;
	penBlue = 0;
}

void Pen::Draw()
{
	Area::DrawArea(CANVAS, Color::CANVAS);
	Area::DrawArea(changeColor.bArea, Color::AREA);
	Area::DrawArea(eraser.bArea, Color::AREA);
	Area::DrawArea(changeWidth.bArea, Color::AREA);

	if (changeColor.isClickArea == true)
	{
		DrawCircle(100, 500, 20, Color::CHANGE_CIRCLE, TRUE); // 確認のために描画
	}
}

void Pen::SetMousePosition(point playerMouse)
{
	pMouse = playerMouse;
}

bool Pen::IsCanUse(bool* isCanUsePen)
{
	// キャンバス内にあるなら使用可能　ないなら使用不可
	if (Area::IsInArea(CANVAS, pMouse))
	{
		*isCanUsePen = true;
		return true;
	}
	return false;
}

void Pen::SetColor(int* penColor)
{
	*penColor = GetColor(penRed, penGreen, penBlue);
}

void Pen::UpdateChangePenWidth(point mouse, float* lineWidth, bool isClick, bool isDrag)
{
	int y = (mouse.y - WIDTH_LINE_TOP.y);
	if (isClick == true)
	{
		*lineWidth = y / 4;
	}
}

// 色を変える処理、中身はまだ
void Pen::ChangeColor(int* color)
{
	if (Area::IsInArea(changeColor.bArea, pMouse) == true)
	{
		if (changeColor.isClickArea == true)
		{
			changeColor.isClickArea = false;
		}
		else
		{
			changeColor.isClickArea = true;
		}

		if (changeColor.isClickArea == true)
		{
			// ここで色を変える処理
		}
	}
}

// こっちに正しい処理をかく
void Pen::ChangeWidth(float* lineWidth)
{
	if (Area::IsInArea(changeWidth.bArea, pMouse) == true)
	{
		if (changeWidth.isClickArea == true)
		{
			changeWidth.isClickArea = false;
		}
		else
		{
			changeWidth.isClickArea = true;
		}

		if (changeWidth.isClickArea == true)
		{
			// 線の太さ変更の処理
			int y = (pMouse.y - WIDTH_LINE_TOP.y);
			*lineWidth = y / 4;
		}
	}
}

void Pen::Erase(int* color)
{
	if (Area::IsInArea(eraser.bArea, pMouse) == true)
	{
		if (eraser.isClickArea == true)
		{
			eraser.isClickArea = false;
			*color = GetColor(penRed, penGreen, penBlue);
		}
		else
		{
			eraser.isClickArea = true;
			*color = Color::ERASER;
		}
	}
}

void Pen::DrawChangePenWidth(float lineWidth)
{
	if (changeWidth.isClickArea == true)
	{
		point p1 = WIDTH_LINE_TOP;
		point p2 = WIDTH_LINE_DOWN;
		DrawLine(p1.x, p1.y, p2.x, p2.y, Color::WIDTH_LINE, WIDTH_LINE_WIDTH);
		DrawCircle(p1.x, p1.y + lineWidth * 4, lineWidth / 2, Color::PEN_CIRCLE, TRUE);
	}
}

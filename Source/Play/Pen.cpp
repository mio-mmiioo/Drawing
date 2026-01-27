#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"

namespace Pen
{
	const area CHANGE_PEN_WIDTH = { 80, 100, 120, 340 }; // ペンの太さを変更する場所
	const point WIDTH_LINE_TOP = { 100, 120 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 100, 320 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 2.0f; // ペンの太さ変更線の太さ

	const area CANVAS = { 50, 50, 650, 550 }; // 絵が描ける範囲
}

void Pen::Init()
{

}

void Pen::UpdateChangePenWidth(point mouse, float* lineWidth, bool isClick, bool isDrag)
{
	int y = (mouse.y - WIDTH_LINE_TOP.y);
	if (isClick == true)
	{
		*lineWidth = y / 4;
	}
}

void Pen::DrawCanvas()
{
	area a = CANVAS;
	DrawBox(a.leftTop.x, a.leftTop.y, a.rightDown.x, a.rightDown.y, Color::CANVAS, TRUE);
}

void Pen::DrawChangePenWidth(float lineWidth)
{
	point p1 = WIDTH_LINE_TOP;
	point p2 = WIDTH_LINE_DOWN;
	DrawLine(p1.x, p1.y, p2.x, p2.y, Color::WIDTH_LINE, WIDTH_LINE_WIDTH);
	DrawCircle(p1.x, p1.y + lineWidth * 4, lineWidth / 2, Color::PEN_CIRCLE, TRUE);
}

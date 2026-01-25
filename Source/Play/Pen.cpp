#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"

namespace Pen
{
	const point WIDTH_LINE_TOP = { 100, 120 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 100, 320 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 10.0f; // ペンの太さ変更線の太さ
}

void Pen::Init()
{

}

void Pen::UpdateChangePenWidth(point mouse, float lineWidth)
{

}

void Pen::DrawChangePenWidth(float lineWidth)
{
	point p1 = WIDTH_LINE_TOP;
	point p2 = WIDTH_LINE_DOWN;
	DrawLine(p1.x, p1.y, p2.x, p2.y, Color::WIDTH_LINE, WIDTH_LINE_WIDTH);
	DrawCircle(p1.x, p1.y + lineWidth * 4, lineWidth / 2, Color::PEN_CIRCLE, TRUE);
}

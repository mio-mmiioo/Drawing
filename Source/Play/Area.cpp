#include "Area.h"
#include "DxLib.h"

bool Area::CheckPointDistance(point p1, point p2, float distance)
{
	float d = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	if (distance * distance > d)
	{
		return true;
	}
	return false;
}

bool Area::IsInArea(area a, point p)
{
	if (a.leftTop.x < p.x && p.x < a.rightDown.x)
	{
		if (a.leftTop.y < p.y && p.y < a.rightDown.y)
		{
			return true;
		}
	}
	return false;
}

void Area::IsClickArea(area a, point p, bool* isClickArea)
{
	if (isClickArea == nullptr)
	{
		return;
	}

	if (IsInArea(a, p) == true)
	{
		if (*isClickArea == true)
		{
			*isClickArea = false;
		}
		else
		{
			*isClickArea = true;
		}
	}
}

void Area::DrawArea(area a, int buttonColor)
{
	int x1 = a.leftTop.x;
	int y1 = a.leftTop.y;
	int x2 = a.rightDown.x;
	int y2 = a.rightDown.y;
	DrawBox(x1, y1, x2, y2, buttonColor, TRUE);
}

void Area::DrawButton1(button b, int color)
{
	DrawArea(b.bArea, color);
	if (b.isClickArea == true)
	{
		DrawArea(b.cArea, color);
	}
}

void Area::DrawButton2(button b, int color)
{
	if (b.isClickArea == true)
	{
		DrawArea(b.cArea, color);
	}
	else
	{
		DrawArea(b.bArea, color);
	}
}

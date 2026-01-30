#include "Area.h"
#include "DxLib.h"

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

void Area::DrawArea(area a, int buttonColor)
{
	int x1 = a.leftTop.x;
	int y1 = a.leftTop.y;
	int x2 = a.rightDown.x;
	int y2 = a.rightDown.y;
	DrawBox(x1, y1, x2, y2, buttonColor, TRUE);
}

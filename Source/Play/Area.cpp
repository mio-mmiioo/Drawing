#include "Area.h"
#include "DxLib.h"

bool Area::IsInArea(button b, point p)
{
	if (b.bArea.leftTop.x < p.x && p.x < b.bArea.rightDown.x)
	{
		if (b.bArea.leftTop.y < p.y && p.y < b.bArea.rightDown.y)
		{
			return true;
		}
	}
	return false;
}

void Area::DrawButton(button b, int buttonColor)
{
	int x1 = b.bArea.leftTop.x;
	int y1 = b.bArea.leftTop.y;
	int x2 = b.bArea.rightDown.x;
	int y2 = b.bArea.rightDown.y;
	DrawBox(x1, y1, x2, y2, buttonColor, TRUE);
}

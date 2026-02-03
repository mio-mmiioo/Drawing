#include "Image.h"
#include "DxLib.h"

void Image::MakeImage(area a, int* hImage)
{
	int width = a.rightDown.x - a.leftTop.x;
	int height = a.rightDown.y - a.leftTop.y;
	if (*hImage > 0)
	{
		DeleteGraph(*hImage);
	}
	*hImage = MakeGraph(width, height);
	GetDrawScreenGraph(a.leftTop.x, a.leftTop.y, a.rightDown.x, a.rightDown.y, *hImage);
}

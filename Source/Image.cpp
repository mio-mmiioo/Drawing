#include "Image.h"
#include "DxLib.h"
#include <assert.h>

namespace Image
{
	std::map<std::string, int> hImage; // ‰æ‘œƒf[ƒ^
}

void Image::Init()
{
	hImage["b-EnterRoom"] = LoadGraph("data/image/b-EnterRoom.png");
	hImage["c-EnterRoom"] = LoadGraph("data/image/c-EnterRoom.png");
	hImage["b-MakeRoom"] = LoadGraph("data/image/b-MakeRoom.png");
	hImage["c-MakeRoom"] = LoadGraph("data/image/c-MakeRoom.png");
	hImage["b-Eraser"] = LoadGraph("data/image/b-Eraser.png");
	hImage["c-Eraser"] = LoadGraph("data/image/c-Eraser.png");
	hImage["b-ChangeWidth"] = LoadGraph("data/image/b-ChangeWidth.png");
	hImage["c-ChangeWidth"] = LoadGraph("data/image/c-ChangeWidth.png");
	hImage["b-ChangeColor"] = LoadGraph("data/image/b-ChangeColor.png");
	hImage["c-ChangeColor"] = LoadGraph("data/image/c-ChangeColor.png");
}

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

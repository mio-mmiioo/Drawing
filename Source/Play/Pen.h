#pragma once
#include "Area.h"

namespace Pen
{
	void Init();
	void Draw();
	void SetMousePosition(point playerMouse);
	bool IsCanUse(bool* isCanUsePen);
	void MakeCanvasImage(int* hImage); // 引数に、キャンバスに書かれている絵を画像として保存する
	void SetColor(int* color);

	void ChangeColor(int* color);
	void ChangeWidth(float* lineWidth);
	void Erase(int* color);

	void DrawChangePenWidth(float lineWidth);
}

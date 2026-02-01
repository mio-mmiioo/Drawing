#pragma once
#include "Area.h"

namespace Pen
{
	void Init();
	void Draw();
	void SetMousePosition(point playerMouse);
	bool IsCanUse(bool* isCanUsePen);
	void SetColor(int* penColor);

	void UpdateChangePenWidth(float* lineWidth);

	void ChangeColor(int* color);
	void ChangeWidth(float* lineWidth);
	void Erase(int* color);

	void DrawChangePenWidth(float lineWidth);
}

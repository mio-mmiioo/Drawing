#pragma once
#include "Area.h"

namespace Pen
{
	void Init();


	void UpdateChangePenWidth(point mouse, float* lineWidth, bool isClick, bool isDrag);

	void DrawCanvas();
	void DrawChangePenWidth(float lineWidth);
}

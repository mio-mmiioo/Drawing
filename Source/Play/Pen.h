#pragma once

namespace Pen
{
	struct point
	{
		int x;
		int y;
	};

	void Init();

	void UpdateChangePenWidth(point mouse, float lineWidth);

	void DrawChangePenWidth(float lineWidth);
}

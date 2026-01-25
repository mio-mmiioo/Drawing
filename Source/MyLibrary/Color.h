#pragma once
#include "DxLib.h"

namespace Color
{
	const int BLACK = GetColor(0, 0, 0);
	const int WHITE = GetColor(255, 255, 255);
	const int RED = GetColor(255, 0, 0);
	const int GREEN = GetColor(0, 255, 0);

	// テキストカラー
	const int TEXT = WHITE;

	// Playerで使用
	const int LINE = RED;
	const int ERASER = BLACK;
	const int AREA = GREEN;
	const int CHANGE_CIRCLE = WHITE;
}

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
	const int ERASER = WHITE;
	const int AREA = GetColor(100, 200, 100);
	const int CHANGE_CIRCLE = WHITE;

	// Penで使用
	const int CANVAS = WHITE;
	const int PEN_CIRCLE = BLACK;
	const int WIDTH_LINE = BLACK; // 線の太さのバー
}

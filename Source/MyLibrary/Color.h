#pragma once
#include "DxLib.h"
#include "../Play/Area.h"

struct MY_HSV
{
	float h; // 色相 0～360 角度で色を決める
	float s; // 彩度 0～1 1に近いほど鮮やかになる
	float v; // 明度 0～1 １に近いほど明るくなる
};

struct MY_RGB
{
	int red; // 赤
	int green; // 緑
	int blue; // 青
};

namespace Color
{
	MY_RGB HSVtoRGB(float h, float s, float v);
	MY_HSV RGBtoHSV(MY_RGB rgb);
	int GetColorMYRGB(MY_RGB myRGB);
	
	const int BLACK = GetColor(0, 0, 0);
	const int WHITE = GetColor(255, 255, 255);
	const int RED = GetColor(255, 0, 0);
	const int GREEN = GetColor(0, 255, 0);

	// テキストカラー
	const int TEXT = WHITE;

	// TitleScreen
	const int MAKE_ROOM = GetColor(100, 200, 100);
	const int ENTER_ROOM = GetColor(100, 200, 100);
	const int RULE = GetColor(100, 200, 100);

	// Playerで使用
	const int LINE = RED;
	const int ERASER = WHITE;
	const int AREA = GetColor(100, 200, 100);
	const int CHANGE_CIRCLE = BLACK;

	// Penで使用
	const int CANVAS = WHITE;
	const int B_ERASER = WHITE;
	const int B_WIDTH = RED;
	const int B_COLOR = GREEN;
	const int PEN_CIRCLE = BLACK;
	const int WIDTH_LINE = BLACK; // 線の太さのバー
}
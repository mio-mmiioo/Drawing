#pragma once

// 2Dの座標
struct point
{
	int x;
	int y;
};

// 2点に囲まれた範囲
struct area
{
	point leftTop; // 左上の座標
	point rightDown; // 右下の座標
};

struct button
{
	area bArea;
	bool isClickArea; // true → ボタンをクリックした
};

namespace Area
{
	bool IsInArea(button b, point p); // true → 座標がボタンの範囲内にある
	void DrawButton(button b, int buttonColor); // ボタンを指定した色で描画する
}

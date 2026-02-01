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
	area bArea; // ボタンのエリア
	area cArea; // ボタンを押した後に展開されるエリア
	bool isClickArea; // true → ボタンをクリックした
};

namespace Area
{
	bool IsInArea(area a, point p); // true → 座標がボタンの範囲内にある
	void DrawArea(area a, int buttonColor); // ボタンを指定した色で描画する
}

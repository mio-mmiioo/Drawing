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

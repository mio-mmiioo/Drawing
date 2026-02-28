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
	int hImage; // 画像
	int color;	// 色
};

struct button
{
	area bArea; // ボタンのエリア
	area cArea; // ボタンを押した後に展開されるエリア
	bool isClickArea; // true → ボタンをクリックした
};

namespace Area
{
	bool CheckPointDistance(point p1, point p2, float distance); // true → distanceの範囲内にp1とp2が存在する
	bool IsInArea(area a, point p); // true → 座標がボタンの範囲内にある
	void IsClickArea(area a, point p, bool* isClickArea); // isCliclkAreaにフラグをセットする
	void DrawArea(area a, int buttonColor); // エリアを指定した色で描画する
	void DrawButton1(button b, int color); // フラグがtrueの時、bAreaとcAreaのどちらも描画する
	void DrawButton2(button b, int color); // フラグがtrueの時、cAreaのみ描画
}

#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"
#include "../../ImGui/imgui.h"
#include "../Image.h"
#include "../Data.h"
#include <vector>

#define HUE_OFFSET 180.0f; // 色相のオフセット

namespace Pen
{
	void DrawPalette(int radius, point circleCenter); // パレットの描画 ※負荷がかかる処理なので、毎フレーム書かないこと

	const point WIDTH_LINE_TOP = { 780, 320 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 780, 480 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 2.0f; // ペンの太さ変更線の太さ

	const float MIN_PEN_WIDTH = 10.0f; // ペンの太さの最小半径
	const float MAX_PEN_WIDTH = 20.0f; // ペンの太さの最大半径
	const float PEN_BASE_SIZE = (float)(WIDTH_LINE_DOWN.y - WIDTH_LINE_TOP.y) / (MAX_PEN_WIDTH - MIN_PEN_WIDTH);

	
	// 色変更関連
	const int MAX_VALUE = 200; // 輝度
	const float SELECT_COLOR_CIRCLE_R = 5.0f; // 選択されている色を示す円の半径
	const float CURRENT_COLOR_CIRCLE_R = 10.0f; // 現在の色を示す円の半径

	button changeColor; // 色を変更
	button changeWidth; // 線の幅を変更
	button eraser; // 消しゴム
	
	area canvas; // キャンバスの範囲
	area value; // 輝度
	area colorPalette; // カラーパレットの範囲
	area changeColorImageArea; // 色変更の画像の範囲
	area changeWidthClick; // 線の太さを変更できる範囲

	point currentColorCircle; // 現在の色を示す円の位置
	point pMouse; // playerのマウスの座標

	MY_RGB penRGB; // ペンの色 RGB
	MY_HSV penHSV; // ペンの色 HSV

	// 画像
	int hColorPaletteImage; // カラーパレットの画像
}

void Pen::Init()
{
	canvas = Data::areaList["Canvas"]; // 絵が描ける範囲
	eraser = { Data::areaList["b-Eraser"], Data::areaList["c-Eraser"], false};
	changeWidth = { Data::areaList["b-ChangeWidth"], Data::areaList["c-ChangeWidth"], false };
	changeColor = { Data::areaList["b-ChangeColor"], Data::areaList["c-ChangeColor"], false };
	value = Data::areaList["c-ColorValue"];
	colorPalette = Data::areaList["c-ColorPalette"];
	changeColorImageArea = Data::areaList["ColorImage"];
	changeWidthClick = Data::areaList["c-ChangeWidthClick"];
	currentColorCircle = { 900, 250 };
	penRGB = { 0, 100, 0 };
	penHSV = Color::RGBtoHSV(penRGB);

	hColorPaletteImage = -1;

	int radius = (colorPalette.rightDown.x - colorPalette.leftTop.x) / 2;
	point center = { colorPalette.leftTop.x + radius, colorPalette.leftTop.y + radius };
	DrawPalette(radius, center);

	// 現在の色の表示
	DrawCircle(currentColorCircle.x, currentColorCircle.y, CURRENT_COLOR_CIRCLE_R, Color::GetColorMYRGB(penRGB), TRUE);
	Image::MakeImage(changeColorImageArea, &hColorPaletteImage);
}

void Pen::Draw()
{
	Area::DrawArea(canvas, Color::CANVAS);
	Area::DrawArea(changeColor.bArea, Color::B_COLOR);
	Area::DrawArea(eraser.bArea, Color::B_ERASER);
	Area::DrawArea(changeWidth.bArea, Color::B_WIDTH);

	// 色パレットの描画
	if (changeColor.isClickArea == true)
	{
		DrawGraph(changeColorImageArea.leftTop.x, changeColorImageArea.leftTop.y, hColorPaletteImage, TRUE);
	}
}

void Pen::SetMousePosition(point playerMouse)
{
	pMouse = playerMouse;
}

bool Pen::IsCanUse(bool* isCanUsePen)
{
	// キャンバス内にあるなら使用可能　ないなら使用不可
	if (Area::IsInArea(canvas, pMouse))
	{
		*isCanUsePen = true;
		return true;
	}
	return false;
}

void Pen::MakeCanvasImage(int* hImage)
{
	Image::MakeImage(canvas, hImage);
}

void Pen::SetColor(int* color)
{
	*color = Color::GetColorMYRGB(penRGB);
}

// 色を変える処理、中身はまだ
void Pen::ChangeColor(int* color)
{
	Area::IsClickArea(changeColor.bArea, pMouse, &changeColor.isClickArea);

	if (changeColor.isClickArea == true)
	{
		// ここで色を変える処理
		int radius = (colorPalette.rightDown.x - colorPalette.leftTop.x) / 2;
		point center = { colorPalette.leftTop.x + radius, colorPalette.leftTop.y + radius };

		// カラーパレットとマウスの距離が一定以内の場合
		if (Area::CheckPointDistance(center, pMouse, radius) == true)
		{
			penHSV.h = (float)(atan2((pMouse.y - center.y), (pMouse.x - center.x)) * 180.0f / DX_PI) + HUE_OFFSET;
			if (penHSV.h < 0)
			{
				penHSV.h += 360.0f;
			}
			else if (penHSV.h > 360.0f)
			{
				penHSV.h -= 360.0f;
			}
			float dist = (pMouse.x - center.x) * (pMouse.x - center.x) + (pMouse.y - center.y) * (pMouse.y - center.y);
			dist = sqrtf(dist);
			penHSV.s = dist / radius;
		}

		// 輝度変更
		if (Area::IsInArea(value, pMouse) == true)
		{
			float x = pMouse.x - value.leftTop.x;
			penHSV.v = x / (float)MAX_VALUE;
		}

		penRGB = Color::HSVtoRGB(penHSV.h, penHSV.s, penHSV.v);
		*color = Color::GetColorMYRGB(penRGB);

		// 現在の色の表示
		DrawCircle(currentColorCircle.x, currentColorCircle.y, CURRENT_COLOR_CIRCLE_R, *color, TRUE);
		DrawPalette(radius, center);
		Image::MakeImage(changeColorImageArea, &hColorPaletteImage); // 画像として保存する ※毎回描画すると処理が重くなる可能性があるため
	}
}

void Pen::ChangeWidth(float* lineWidth)
{
	Area::IsClickArea(changeWidth.bArea, pMouse, &changeWidth.isClickArea);
	if (changeWidth.isClickArea == true && Area::IsInArea(changeWidthClick, pMouse))
	{
		// 線の太さ変更の処理
		int y = (pMouse.y - WIDTH_LINE_TOP.y);
		*lineWidth = y / PEN_BASE_SIZE + MIN_PEN_WIDTH;
	}
}

void Pen::Erase(int* color)
{
	if (Area::IsInArea(eraser.bArea, pMouse) == true)
	{
		if (eraser.isClickArea == true)
		{
			eraser.isClickArea = false;
			*color = GetColor(penRGB.red, penRGB.green, penRGB.blue);
		}
		else
		{
			eraser.isClickArea = true;
			*color = Color::ERASER;
		}
	}
}

void Pen::DrawChangePenWidth(float lineWidth)
{
	if (changeWidth.isClickArea == true)
	{
		point p1 = WIDTH_LINE_TOP;
		point p2 = WIDTH_LINE_DOWN;
		DrawLine(p1.x, p1.y, p2.x, p2.y, Color::WIDTH_LINE, WIDTH_LINE_WIDTH);
		DrawCircle(p1.x, p1.y + (lineWidth - MIN_PEN_WIDTH) * PEN_BASE_SIZE, lineWidth / 2, Color::PEN_CIRCLE, TRUE);
	}
}

void Pen::DrawPalette(int radius, point circleCenter)
{
	// 円形パレット
	for (int y = -radius; y <= radius; y++) {
		for (int x = -radius; x <= radius; x++) {
			float d = sqrt(x * x + y * y);
			if (d <= radius) {
				// 角度と距離を計算
				float h = (float)(atan2(y, x) * 180.0f / DX_PI) + HUE_OFFSET;
				float s = d / radius;
				MY_RGB c = Color::HSVtoRGB(h, s, 1.0f);
				DrawPixel(circleCenter.x + x, circleCenter.y + y, GetColor(c.red, c.green, c.blue));
			}
		}
	}

	// 輝度
	for (int i = 0; i < MAX_VALUE; i++) {
		int gray = (int)(i * (255.0f / (float)MAX_VALUE));
		DrawLine(value.leftTop.x + i, value.leftTop.y, value.leftTop.x + i,
			value.rightDown.y, GetColor(gray, gray, gray));
	}
}

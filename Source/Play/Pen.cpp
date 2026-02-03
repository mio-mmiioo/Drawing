#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"
#include "../../ImGui/imgui.h"
#include "../Image.h"
#include <vector>

#define HUE_OFFSET 180.0f; // 色相のオフセット

namespace Pen
{
	const area CHANGE_PEN_WIDTH = { 80, 100, 120, 340 }; // ペンの太さを変更する場所
	const point WIDTH_LINE_TOP = { 100, 120 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 100, 320 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 2.0f; // ペンの太さ変更線の太さ

	const area CANVAS = { 50, 50, 650, 550 }; // 絵が描ける範囲

	// 色変更関連
	const int MAX_VALUE = 200; // 輝度
	const float SELECT_COLOR_CIRCLE_R = 5.0f; // 選択されている色を示す円の半径
	const float CURRENT_COLOR_CIRCLE_R = 10.0f; // 現在の色を示す円の半径
	


	button changeColor; // 色を変更
	button changeWidth; // 線の幅を変更
	button eraser; // 消しゴム
	
	area value; // 輝度
	area colorPalette; // 画像として切り抜くカラーパレット

	point currentColorCircle; // 現在の色を示す円の位置
	point pMouse; // playerのマウスの座標

	std::vector<area> drawAreaList; 
	MY_RGB penRGB; // ペンの色 RGB
	MY_HSV penHSV; // ペンの色 HSV

	// 画像
	int hColorPaletteImage; // カラーパレットの画像
}

void Pen::Init()
{
	eraser = { 800, 200, 820, 220, 0, 0, 0, 0, false };
	changeWidth = { 820, 200, 840, 220, 0, 0, 0, 0, false };
	changeColor = { 840, 200, 860, 220, 800, 300, 1000, 500, false };
	value = { 800, 520, 800 + MAX_VALUE, 550 };
	colorPalette = { 800, 200, 1000, 700 };
	currentColorCircle = { 900, 250 };
	penRGB = { 0, 100, 0 };
	penHSV = Color::RGBtoHSV(penRGB);

	hColorPaletteImage = -1;

	int radius = (changeColor.cArea.rightDown.x - changeColor.cArea.leftTop.x) / 2;
	int centerX = changeColor.cArea.leftTop.x + radius;
	int centerY = changeColor.cArea.leftTop.y + radius;
	// 円形パレット
	for (int y = -radius; y <= radius; y++) {
		for (int x = -radius; x <= radius; x++) {
			float d = sqrt(x * x + y * y);
			if (d <= radius) {
				// 角度と距離を計算
				float h = (float)(atan2(y, x) * 180.0f / DX_PI) + HUE_OFFSET;
				float s = d / radius;
				MY_RGB c = Color::HSVtoRGB(h, s, 1.0f);
				DrawPixel(centerX + x, centerY + y, GetColor(c.red, c.green, c.blue));
			}
		}
	}

	// 輝度
	for (int i = 0; i < MAX_VALUE; i++) {
		int gray = (int)(i * ((float)255 / (float)MAX_VALUE));
		DrawLine(value.leftTop.x + i, value.leftTop.y, value.leftTop.x + i,
			value.rightDown.y, GetColor(gray, gray, gray));
	}

	// 現在の色の表示
	DrawCircle(currentColorCircle.x, currentColorCircle.y, CURRENT_COLOR_CIRCLE_R, Color::GetColorMYRGB(penRGB), TRUE);

	Image::MakeImage(colorPalette, &hColorPaletteImage);
}

void Pen::Draw()
{
	Area::DrawArea(CANVAS, Color::CANVAS);
	Area::DrawArea(changeColor.bArea, Color::B_COLOR);
	Area::DrawArea(eraser.bArea, Color::B_ERASER);
	Area::DrawArea(changeWidth.bArea, Color::B_WIDTH);

	// 色パレットの描画
	if (changeColor.isClickArea == true)
	{
		DrawGraph(colorPalette.leftTop.x, colorPalette.leftTop.y, hColorPaletteImage, TRUE);
	}

}

void Pen::SetMousePosition(point playerMouse)
{
	pMouse = playerMouse;
}

bool Pen::IsCanUse(bool* isCanUsePen)
{
	// キャンバス内にあるなら使用可能　ないなら使用不可
	if (Area::IsInArea(CANVAS, pMouse))
	{
		*isCanUsePen = true;
		return true;
	}
	return false;
}

void Pen::MakeCanvasImage(int* hImage)
{
	Image::MakeImage(CANVAS, hImage);
}

void Pen::SetColor(int* color)
{
	*color = GetColor(penRGB.red, penRGB.green, penRGB.blue);
}

void Pen::UpdateChangePenWidth(float* lineWidth)
{
	int y = (pMouse.y - WIDTH_LINE_TOP.y);
	*lineWidth = y / 4;
}

// 色を変える処理、中身はまだ
void Pen::ChangeColor(int* color)
{
	if (Area::IsInArea(changeColor.bArea, pMouse) == true)
	{
		if (changeColor.isClickArea == true)
		{
			changeColor.isClickArea = false;
		}
		else
		{
			changeColor.isClickArea = true;
		}
	}

	if (changeColor.isClickArea == true)
	{
		// ここで色を変える処理
		int radius = (changeColor.cArea.rightDown.x - changeColor.cArea.leftTop.x) / 2;
		point center = {
			changeColor.cArea.leftTop.x + radius,
			changeColor.cArea.leftTop.y + radius
		};

		// カラーパレットとマウスの距離が一定以内の場合
		if (Area::CheckPointDistance(center, pMouse, radius) == true)
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
						DrawPixel(center.x + x, center.y + y, GetColor(c.red, c.green, c.blue));
					}
				}
			}

			// 輝度
			for (int i = 0; i < MAX_VALUE; i++) {
				int gray = (int)(i * ((float)255 / (float)MAX_VALUE));
				DrawLine(value.leftTop.x + i, value.leftTop.y, value.leftTop.x + i,
					value.rightDown.y, GetColor(gray, gray, gray));
			}

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


			// 輝度変更（未実装）
			penHSV.v = 1.0f;



			penRGB = Color::HSVtoRGB(penHSV.h, penHSV.s, penHSV.v);
			*color = Color::GetColorMYRGB(penRGB);

			// 現在の色の表示
			DrawCircle(currentColorCircle.x, currentColorCircle.y, CURRENT_COLOR_CIRCLE_R, Color::GetColorMYRGB(penRGB), TRUE);

			Image::MakeImage(colorPalette, &hColorPaletteImage); // 画像として保存する ※毎回描画すると処理が重くなる可能性があるため
		}
	}
}

void Pen::ChangeWidth(float* lineWidth)
{
	if (Area::IsInArea(changeWidth.bArea, pMouse) == true)
	{
		if (changeWidth.isClickArea == true)
		{
			changeWidth.isClickArea = false;
		}
		else
		{
			changeWidth.isClickArea = true;
		}

		if (changeWidth.isClickArea == true)
		{
			// 線の太さ変更の処理
			int y = (pMouse.y - WIDTH_LINE_TOP.y);
			*lineWidth = y / 4;
		}
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
		DrawCircle(p1.x, p1.y + lineWidth * 4, lineWidth / 2, Color::PEN_CIRCLE, TRUE);
	}
}

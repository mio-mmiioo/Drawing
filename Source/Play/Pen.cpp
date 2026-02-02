#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"
#include "../../ImGui/imgui.h"
#include <vector>

namespace Pen
{
	const area CHANGE_PEN_WIDTH = { 80, 100, 120, 340 }; // ペンの太さを変更する場所
	const point WIDTH_LINE_TOP = { 100, 120 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 100, 320 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 2.0f; // ペンの太さ変更線の太さ

	const area CANVAS = { 50, 50, 650, 550 }; // 絵が描ける範囲

	
	button changeColor; // 色を変更
	button changeWidth; // 線の幅を変更
	button eraser; // 消しゴム

	point pMouse; // playerのマウスの座標

	std::vector<area> drawAreaList; 
	MY_RGB penColor; // ペンの色
	//int penRed; // ペンの赤色の値
	//int penGreen; // ペンの緑色の値
	//int penBlue; // ペンの青色の値

	// 画像
	int hColorPaletteImage; // カラーパレットの画像
}

void Pen::Init()
{
	eraser = { 800, 200, 820, 220, 0, 0, 0, 0, false };
	changeWidth = { 820, 200, 840, 220, 0, 0, 0, 0, false };
	changeColor = { 840, 200, 860, 220, 800, 300, 1000, 500, false };

	penColor = { 0, 100, 0 };
	//penRed = 0;
	//penGreen = 100;
	//penBlue = 0;
}

void Pen::Draw()
{
	Area::DrawArea(CANVAS, Color::CANVAS);
	Area::DrawArea(changeColor.bArea, Color::B_COLOR);
	Area::DrawArea(eraser.bArea, Color::B_ERASER);
	Area::DrawArea(changeWidth.bArea, Color::B_WIDTH);

	if (changeColor.isClickArea == true)
	{
		DrawCircle(100, 500, 20, Color::CHANGE_CIRCLE, TRUE); // 確認のために描画
	}

	// 色パレットの描画 ※画像に置き換える/毎回描画すると処理が重くなる可能性があるから
	{
		int radius = (changeColor.cArea.rightDown.x - changeColor.cArea.leftTop.x) / 2;
		int centerX = changeColor.cArea.leftTop.x + radius;
		int centerY = changeColor.cArea.leftTop.y + radius;
		
		// 現在の色の表示
		DrawCircle(centerX, changeColor.cArea.leftTop.y - 20, 10.0f, Color::GetColorMYRGB(penColor), TRUE);
		
		// 円形パレット
		for (int y = -radius; y <= radius; y++) {
			for (int x = -radius; x <= radius; x++) {
				float d = sqrt(x * x + y * y);
				if (d <= radius) {
					// 角度と距離を計算
					float h = (float)(atan2(y, x) * 180.0f / DX_PI) + 180.0f;
					float s = d / radius;
					MY_RGB c = Color::HSVtoRGB(h, s, 1.0f);
					DrawPixel(centerX + x, centerY + y, GetColor(c.red, c.green, c.blue));

					if (c.red == penColor.red && c.green == penColor.green && c.blue == penColor.blue)
					{
						DrawCircle(centerX + x, centerY + y, Color::BLACK, FALSE);
					}
				}
			}
		}

		// 輝度
		for (int i = 0; i < 200; i++) {
			int gray = (int)(i * (255.0 / 200.0));
			DrawLine(changeColor.cArea.leftTop.x + i, changeColor.cArea.rightDown.y + 20, changeColor.cArea.leftTop.x + i,
				changeColor.cArea.rightDown.y + 50, GetColor(gray, gray, gray));
		}

		// 現在の色を表示する
		MY_HSV hsv = Color::RGBtoHSV(penColor);
		DrawCircle(centerX, centerY, 5.0f, Color::BLACK, FALSE);
		ImGui::Begin("RGB");
		MY_RGB rgb = Color::HSVtoRGB(hsv.h, hsv.s, hsv.v);
		ImGui::Text("H;%d, S:%d, V:%d", hsv.h, hsv.s, hsv.v);
		ImGui::Text("R;%d, G:%d, B:%d", rgb.red, rgb.green, rgb.blue);
		ImGui::End();
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

void Pen::SetColor(int* color)
{
	*color = GetColor(penColor.red, penColor.green, penColor.blue);
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

		if (changeColor.isClickArea == true)
		{
			// ここで色を変える処理
			int radius = (changeColor.cArea.rightDown.x - changeColor.cArea.leftTop.x) / 2;
			int centerX = changeColor.cArea.leftTop.x + radius;
			int centerY = changeColor.cArea.leftTop.y + radius;
			//if ()

		}
	}
}

// こっちに正しい処理をかく
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
			*color = GetColor(penColor.red, penColor.green, penColor.blue);
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
